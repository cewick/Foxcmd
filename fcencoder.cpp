#include "fcencoder.h"
#include "fcpreferences.h"
#include "fcmainwindow.h"   //*****added ver 0.6 *******

#include <QIODevice>
#include <QAudioFormat>
#include <QtCore>
#include <QSettings>
#include <QDebug>

#include <math.h>

#define COMMAND_DELAY 16

FCEncoder::FCEncoder(const QAudioFormat &format, FCCommand *command, quint8 address, QObject *parent) :
    QIODevice(parent),
    m_pos(0)
{
    QSettings settings;
    m_gain = settings.value(FC_AUDIO_GAIN_KEY).toFloat();
    m_nretries = settings.value(FC_GENERAL_NRETRIES_KEY).toInt();

    generateData(format, command, address);
}

FCEncoder::~FCEncoder()
{
    qDebug() << "FCEncoder released";
}

// Emulate a Holtek HT12E encoder
//
// When encoding data, the HT12E holds the output low for 36 clock cycles, then high for
// 1 cycle, followed by 8 "address" bits and concludes with 4 "data" bits. The cycle is then
// repeated 4 times. One frame should take 73 clock cycles and the entire transmission
// should take 73 * 4 or 292 clock cycles.
//
void FCEncoder::generateData(const QAudioFormat &format, FCCommand *command, quint8 address)
{
    QSettings settings;
    const quint32 clock = settings.value(FC_AUDIO_CLOCKRATE_KEY).toInt();
    const quint32 channelBytes = format.sampleSize() / 8;
    m_samplesPerTick = quint32(format.sampleRate() / clock);
    // m_nretries == -1 means keep feeding data forever (see readData()) so all we need is one command cycle
    // XXX ignore the retries for right now.
    //int ncycles = m_nretries == -1 ? 4 : (m_nretries + 1) * 4;
    int ncycles = 4;

    qint64 length = 73 * ncycles * m_samplesPerTick * channelBytes;

    if (command->m_command.size() == 3)
    {
        // make room for 3 commands
        length *= 3;
        // add in two 16 second delays
        length += (COMMAND_DELAY * format.sampleRate() * 2);
    }

    m_buffer.resize(length);
    m_pos = 0;

    quint8 *ptr = reinterpret_cast<quint8 *>(m_buffer.data());

    qDebug("clock: %d", clock);
    qDebug("channelBytes: %d", channelBytes);
    qDebug("sampleRate: %d", format.sampleRate());
    qDebug("m_samplesPerTick: %d", m_samplesPerTick);
    qDebug("buffer length: %d", m_buffer.size());
    qDebug("calculated length: %d", (int)length);

    InvertAudio = settings.value(FC_AUDIO_INVERT_KEY).toBool();

    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < ncycles; i++)
        {
            writePreamble();
            for (int j = 0; j < 8; j++)
            {
                const quint8 b = (address >> j) & 0x01;
                    writeBit(b);
            }
            for (int j = 0; j < 4; j++)
            {
                const quint8 b = (((quint32)command->m_command.at(k)) >> j) & 0x01;
                    writeBit(b);
            }
        }

        if (k == 2 || command->m_command.size() == 1)
            break;

        // fill with 16 seconds of zeros
        for (int p = 0; p < (COMMAND_DELAY * format.sampleRate()); p++)
            ptr[m_pos++] = 0;
    }
/*  **************filterBuffer is unused function *****************
    // run the data through a 3-pole low-pass bessel filter
    filterBuffer();
*/
    m_pos = 0;
}

/* *************************unused function ***************************
void FCEncoder::filterBuffer()
{
    m_pos = 0;
}
*/

//***************************** modified for version 0.6 ******************
void FCEncoder::writePreamble()
{
    quint8 *ptr = reinterpret_cast<quint8 *>(m_buffer.data());

    //qDebug("m_pos before preamble: %d", m_pos);

    // the 12 bit preamble lasts 36 clock cycles. 3 cycles per bit.
    for (int i = 0; i < (36 * m_samplesPerTick); i++)
    {
        if(!InvertAudio)
            ptr[m_pos++] = 0x00 * m_gain;
        else
            ptr[m_pos++] = 0xFF * m_gain;

    }

    // 1/3 bit sync period. lasts one clock cycle
    for (int i = 0; i < (1 * m_samplesPerTick); i++)
    {
        if(!InvertAudio)
            ptr[m_pos++] = 0xFF * m_gain;
        else
            ptr[m_pos++] = 0x00 * m_gain;
    }

    //qDebug("m_pos after preamble: %d", m_pos);
}

void FCEncoder::writeBit(quint8 bit)
{
    quint8 *ptr = reinterpret_cast<quint8 *>(m_buffer.data());


    //qDebug("m_pos before writebit[%d], %d", bit, m_pos);

    for (int i = 0; i < m_samplesPerTick; i++)
    {
        if(!InvertAudio)
            ptr[m_pos++] = 0x00 * m_gain;
        else
            ptr[m_pos++] = 0xFF * m_gain;
    }
    for (int i = 0; i < m_samplesPerTick; i++)
    {
        if(!InvertAudio)
            ptr[m_pos++] = bit ? (0x00 * m_gain) : (0xFF * m_gain);
        else
            ptr[m_pos++] = bit ? (0xFF * m_gain) : (0x00 * m_gain);
    }
    for (int i = 0; i < m_samplesPerTick; i++)
    {
        if(!InvertAudio)
            ptr[m_pos++] = 0xFF * m_gain;
        else
            ptr[m_pos++] = 0x00 * m_gain;
    }

    //qDebug("m_pos after bit[%d]: %d", bit, m_pos);
}

void FCEncoder::start()
{
    open(QIODevice::ReadOnly);
}

void FCEncoder::stop()
{
    m_pos = 0;
    close();
}

qint64 FCEncoder::readData(char *data, qint64 len)
{
    // m_nretries == -1 means keep feeding the audio proc data forever
    if (m_nretries == -1)
    {
        qint64 total = 0;
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
        return total;
    }
    else
    {
        const qint64 chunkSize = qMin((m_buffer.size() - m_pos), len);

        memcpy(data, m_buffer.constData() + m_pos, chunkSize);
        m_pos += chunkSize;

        return chunkSize;
    }
}

qint64 FCEncoder::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 FCEncoder::bytesAvailable() const
{
    //return m_buffer.size() + QIODevice::bytesAvailable();
    return (m_buffer.size() - m_pos) + QIODevice::bytesAvailable();
}

