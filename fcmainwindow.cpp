#include <QDebug>
#include <QPushButton>
#include <QRadioButton>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QThread>
#include <QtAlgorithms>
#include <QSettings>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QTimer>
#include <QMessageBox>
#include <QCheckBox>
#include <QVector>

#include "fcmainwindow.h"
#include "ui_fcmainwindow.h"

#include "fcpreferences.h"
#include "fclog.h"
#include "fcabout.h"
#include "fcencoder.h"
#include "fcrig.h"
#include "fccommand.h"

const int BufferSize = 32768;


FCMainWindow::FCMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::FCMainWindow),
    m_audioOutput(0),
    m_encoder(0)
{
    m_ui->setupUi(this);

    QCoreApplication::setOrganizationName("AMSAT");
    QCoreApplication::setOrganizationDomain("amsat.org");
    QCoreApplication::setApplicationName("FoxCom");

    makeCommandTable();

    readPreferences();

    layoutMainWindow();

    updateStatus(FC_IDLE);

    m_preferencesWindow = new FCPreferences(this);

    m_logWindow = new FCLog(this);

    m_rig = new FCRig(this);
}

FCMainWindow::~FCMainWindow()
{
    qDeleteAll(*m_commandTable);
    delete m_commandTable;

    delete m_logWindow;
    delete m_preferencesWindow;
    delete m_rig;
    delete m_ui;
}

//
// Private API
//

void FCMainWindow::layoutMainWindow()
{
    QHBoxLayout *hbox = new QHBoxLayout();

    QGroupBox *groupBox = new QGroupBox(tr("Fox-1 Commands"));
//******** ver 6.2 ********
    cBox = groupBox;
//*************************
    QVBoxLayout *vbox = new QVBoxLayout();

    QRadioButton *button;
    QCheckBox *chk;


    for (int i = 0; i < 2; i++)
    {
        FCCommand *c = qobject_cast<FCCommand *>(m_commandTable->at(i));

        chk = new QCheckBox(c->m_desc, this);
        chk->setProperty("command_index", QVariant(i));
        chk->setChecked(false);

        vbox->addWidget(chk);
    }

    for (int i = 2; i < m_commandTable->size(); i++)
    {
        FCCommand *c = qobject_cast<FCCommand *>(m_commandTable->at(i));

        // FCMainWindow is the parent so we can find them later
        button = new QRadioButton(c->m_desc, this);
        button->setProperty("command_index", QVariant(i));

        if (i == 2)
            button->setChecked(true);

        vbox->addWidget(button);
    }

    //vbox->addStretch(1);

    groupBox->setLayout(vbox);

    m_sendButton = new QPushButton(tr("Send"));
    m_sendButton->setObjectName(tr("sendButton"));
    QObject::connect(m_sendButton,
                     SIGNAL(clicked()),
                     this,
                     SLOT(on_sendButton_clicked()));

    hbox->addWidget(groupBox);
    hbox->addWidget(m_sendButton);

    m_ui->centralWidget->setLayout(hbox);

}

void FCMainWindow::sendCommand(FCCommand *command)
{
    QSettings settings;
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;
    int ret;


    // pop a confirm dialog, if needed
    if (settings.value(FC_GENERAL_CONFIRM_SEND_KEY).toBool())
    {
        QMessageBox::StandardButton button;

        button = QMessageBox::question(this,
                                       tr("Send Command Confirmation"),
                                       tr("You are about to send a command. Are you sure?"));
        if (button == QMessageBox::No)
            return;
    }

    // get the user's current device
    ret = getCurrentDevice(deviceInfo);
    if (ret != 0)
        return;

    // setup the data stream
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    format.setByteOrder(QAudioFormat::BigEndian);
#else
    format.setByteOrder(QAudioFormat::LittleEndian);
#endif
    format.setSampleType(QAudioFormat::UnSignedInt);
    format.setSampleRate(settings.value(FC_AUDIO_SAMPLERATE_KEY).toInt());

    // check to see if this format is compatible with the output device
    if (!deviceInfo.isFormatSupported(format))
    {
        QMessageBox::critical(this,
                              tr("Unsupported Format"),
                              tr("Oops! It appears your chosen audio device doesn't support"
                                 " the format required to send the command."));
        return;
    }

    // cleanup any previous audio objects. we do this here instead of right after
    // the sample had played since QAudioOuput changes its state to QAudio::IdleState
    // a little before the sample given by QIODevice is completely finished playing.
    // it's likely I don't understand how the entire audio system works.
    cleanupAudio();

    // create an audio output
    m_audioOutput = new QAudioOutput(deviceInfo, format);

    // create the encoder (data generator)

    m_encoder = new FCEncoder(format, command, calculate_address());
    m_encoder->start();

    // listen for state changes
    connect(m_audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));


    m_logWindow->log("Sending Command: [ ");
    for (int i = 0; i < command->m_command.size(); i++)
        m_logWindow->log("0x%02x ", command->m_command.at(i));
    m_logWindow->log("]\n");

    // set the volume
    m_audioOutput->setVolume(1.0f);

    // and output the data
    m_audioOutput->start(m_encoder);
}

void FCMainWindow::handleStateChanged(QAudio::State state)
{
    switch (state)
    {
    case QAudio::IdleState:
        qDebug() << "m_audioOutput in QAudio::IdleState";

        // XXX unkey the rig

        updateStatus(FC_IDLE);

        break;

    case QAudio::StoppedState:
        qDebug() << "m_audioOutput in QAudio::StoppedState";

        // stopped for other reasons
        if (m_audioOutput && m_audioOutput->error() != QAudio::NoError)
        {
            QMessageBox::critical(this,
                                  tr("Audio Output Error"),
                                  tr("Oops! There was an error rendering the audio."));
            updateStatus(FC_ERROR);
        }

        break;

    case QAudio::ActiveState:
        qDebug() << "m_audioOutput in QAudio::ActiveState";

        updateStatus(FC_SENDING);

        break;

    case QAudio::SuspendedState:
        qDebug() << "m_audioOutput in QAudio::SuspendedState";
        break;

    default:
        qDebug() << "unknown state!";
        break;
    }
}

int FCMainWindow::getCurrentDevice(QAudioDeviceInfo& info)
{
    QSettings settings;
    QString deviceName;


    deviceName = settings.value(FC_AUDIO_DEVICE_KEY).toString();
    foreach (info, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
        if (deviceName == info.deviceName())
            return 0;

    QMessageBox::critical(this,
                          tr("Device Not Found"),
                          tr("Oops! I can't find your specified output audio device,"
                             " perhaps it has been removed?"));
    return -1;
}

void FCMainWindow::makeCommandTable()
{
    // XXX let's load up the command table from an XML file
    m_commandTable = new QList<FCCommand *>();

    // 0b1000
    m_commandTable->append(new FCCommand(tr("Inhibit TX"), QList<uint>({0x8})));
    // 0b0100
    m_commandTable->append(new FCCommand(tr("Inhibit IHU (power off)"), QList<uint>({0x4})));
    // 0b0000
    m_commandTable->append(new FCCommand(tr("Go To Transponder Mode"), QList<uint>({0x0})));
    // 0b0001
    m_commandTable->append(new FCCommand(tr("Go To Data Mode"), QList<uint>({0x1})));
    // 0b0010
    m_commandTable->append(new FCCommand(tr("Clear Telemetry Min/Max Data"), QList<uint>({0x2, 0x2, 0x2})));
    // 0b0011
    m_commandTable->append(new FCCommand(tr("Go To Safe Mode"), QList<uint>({0x3})));
}

void FCMainWindow::readPreferences()
{
    QSettings settings;

    settings.beginGroup("FCMainWindow");
    move(settings.value("pos", QPoint(400, 400)).toPoint());
    settings.endGroup();
}

void FCMainWindow::writePreferences()
{
    QSettings settings;

    settings.beginGroup("FCMainWindow");
    settings.setValue("pos", pos());
    settings.endGroup();
}

void FCMainWindow::updateStatus(status_state_t state)
{

    switch (state)
    {
        case FC_ERROR:
            m_ui->statusBar->showMessage(tr("Status: ERROR!"), 0);
            m_sendButton->setText(tr("Send"));
            break;
        case FC_IDLE:
            m_ui->statusBar->showMessage(tr("Status: Idle"), 0);
            m_sendButton->setText(tr("Send"));
            break;
        case FC_SENDING:
            m_ui->statusBar->showMessage(tr("Status: Sending..."), 0);
            m_sendButton->setText(tr("Stop"));
            break;
        default:
            break;
    }
}

void FCMainWindow::cleanupAudio()
{
    if (m_audioOutput)
    {
        m_audioOutput->stop();
        delete m_audioOutput;
        m_audioOutput = 0;

    }

    if (m_encoder)
    {
        m_encoder->stop();
        delete m_encoder;
        m_encoder = 0;
    }
}

quint8 FCMainWindow::calculate_address()
{
    QSettings settings;
    const char *callsign;
    const char *password;
    quint8 address = 0x00;


    callsign = _strdup(settings.value(FC_AUTH_CALLSIGN_KEY).toString().toUtf8().constData());
    password = _strdup(settings.value(FC_AUTH_PASSWORD_KEY).toString().toUtf8().constData());

    for (unsigned int i = 0; i < strlen(callsign); i++)
        address += callsign[i];

    for (unsigned int i = 0; i < strlen(password); i++)
        address += password[i];

    free((void *)callsign);
    free((void *)password);

    qDebug("Callsign and password hash to address 0x%02X", address);

    return address;
}


//
// Callbacks
//

void FCMainWindow::on_sendButton_clicked()
{
    int command_index = 0;


    if (m_audioOutput && m_audioOutput->state() ==  QAudio::ActiveState)
    {
        // XXX it's likely that hitting the "Stop" button may introduce a race
        // condition so stopping and cleaning up should be synchronized
        cleanupAudio();
        updateStatus(FC_IDLE);
    }
    else
    {
        // slurp up the hardware commands, if any are selected
//****V6.2 changed this to cBox to limit radio button and check box context to command window
        QList<QRadioButton *> list = cBox->findChildren<QRadioButton *>();
   qDebug("RadioButtons polled: %d",list.size());
        for (int i = 0; i < list.size(); i++)
        {
            QRadioButton *b = qobject_cast<QRadioButton *>(list[i]);

            if (b->isChecked())
                command_index = b->property("command_index").toInt();
        }
    qDebug("RB Index %d",command_index);
        // then OR the selected software command with the hardware command(s)

        QList<QCheckBox *> list2 = cBox->findChildren<QCheckBox *>();
    qDebug("Checkboxes polled: %d",list2.size());
        for (int i = 0; i < list2.size(); i++)

        {
            QCheckBox *b = qobject_cast<QCheckBox *>(list2[i]);

            if (b->isChecked())
                command_index = b->property("command_index").toInt();
        }
    qDebug("CB Index %d",command_index);
        FCCommand *command = m_commandTable->at(command_index);
        for (int i = 0; i < command->m_command.size(); i++)
            qDebug("command to send: 0x%x", command->m_command.at(i));

        sendCommand(command);
    }
}

void FCMainWindow::on_actionPreferences_triggered()
{
    if (m_preferencesWindow->isHidden())
    {
        QDialog::DialogCode code = (QDialog::DialogCode)m_preferencesWindow->exec();

        if (code == QDialog::Accepted)
            m_preferencesWindow->savePreferences();
    }
}

void FCMainWindow::on_actionLog_triggered()
{
    if (m_logWindow->isHidden())
    {
        // XXX load up the log widget here
        m_logWindow->show();
    }
}

void FCMainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void FCMainWindow::on_actionAbout_FoxCom_triggered()
{
    FCAbout p(this);

    p.exec();
}

void FCMainWindow::on_aboutToQuit()
{
    writePreferences();
}
