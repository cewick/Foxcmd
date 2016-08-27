#ifndef FCENCODER_H
#define FCENCODER_H

#include <QObject>
#include <QAudioFormat>
#include <QIODevice>

#include <fccommand.h>

class FCEncoder : public QIODevice
{
    Q_OBJECT
public:
    explicit FCEncoder(const QAudioFormat &format, FCCommand *command, quint8 address, QObject *parent = 0);
    ~FCEncoder();
    
    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;
    qint64 read(char *data, qint64 maxlen);
    bool InvertAudio;

private:
    void generateData(const QAudioFormat &format, FCCommand *command, quint8 address);
    void writePreamble();
    void writeBit(quint8);
//    void filterBuffer();   ****** unused function

    qint64 m_pos;
    QByteArray m_buffer;
    qint32 m_samplesPerTick;
    float m_gain;
    int m_nretries;

};

#endif // FCENCODER_H
