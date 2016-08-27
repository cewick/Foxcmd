#include "fcpreferences.h"
#include "ui_fcpreferences.h"
#include "fcencoder.h"      //**********added ver 0.6 ***************

#include <QAudioDeviceInfo>
#include <QSettings>
#include <QVariant>
#include <QDebug>
#include <QDialog>

FCPreferences::FCPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCPreferences)
{
    ui->setupUi(this);

    populatePreferencesWindow();
}

FCPreferences::~FCPreferences()
{
    delete ui;
}

int FCPreferences::exec()
{
    ui->tabWidget->setCurrentIndex(0);

    return QDialog::exec();
}

void FCPreferences::populatePreferencesWindow()
{
    QAudioDeviceInfo defaultDevice;
    QSettings settings;
    QVariant v;
    int i = 0;


    // populate the device popup
    ui->outputDevice->clear();
    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        if (!settings.contains(FC_AUDIO_DEVICE_KEY))
            settings.setValue(FC_AUDIO_DEVICE_KEY, deviceInfo.deviceName());

        ui->outputDevice->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));

        // look in the settings for which device to select
        if (deviceInfo.deviceName() == settings.value(FC_AUDIO_DEVICE_KEY).toString())
        {
            defaultDevice = deviceInfo;
            ui->outputDevice->setCurrentIndex(i);
        }

        i++;
    }

    // if we don't have any preferences stores yet
    if (!settings.contains(FC_AUDIO_SAMPLERATE_KEY))
    {
        QAudioFormat defaultFormat = defaultDevice.preferredFormat();
        QString sampleRate = QString("%1").arg(defaultFormat.sampleRate());

        settings.setValue(FC_AUDIO_SAMPLERATE_KEY, QVariant(sampleRate));
        settings.setValue(FC_AUDIO_GAIN_KEY, QVariant(1.0f));
        settings.setValue(FC_AUDIO_GAINLABEL_KEY, QVariant(tr("100%")));
        settings.setValue(FC_AUDIO_CLOCKRATE_KEY, QVariant(655));

        settings.setValue(FC_GENERAL_CONFIRM_SEND_KEY, QVariant(true));

        // the default username and password hashes to 0x50
        settings.setValue(FC_AUTH_CALLSIGN_KEY, QVariant(tr("KD0OPN")));
        settings.setValue(FC_AUTH_PASSWORD_KEY, QVariant(tr("SNNBs")));

        settings.setValue(FC_GENERAL_NRETRIES_KEY, QVariant(0));
    }

//*************************** new for version 0.6 ******************************
    if(!settings.contains(FC_AUDIO_INVERT_KEY))
    {
        settings.setValue(FC_AUDIO_INVERT_KEY,QVariant(0));     //initial state of checkbox
    }
    else
    {
        ui->InvBox->setCheckState((Qt::CheckState)settings.value(FC_AUDIO_INVERT_KEY).toInt());
    }
//******************************************************************************


    // the sample rate depends upon the device chosen
    on_outputDevice_activated(ui->outputDevice->currentIndex());


    // and the confirmation checkbox
    ui->confirmCheckBox->setChecked(settings.value(FC_GENERAL_CONFIRM_SEND_KEY).toBool());

    // populate the retry combo
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
            ui->retryBox->addItem(tr("none"), QVariant(i));
        else
            ui->retryBox->addItem(tr("%1").arg(i), QVariant(i));

        if (settings.value(FC_GENERAL_NRETRIES_KEY).toInt() == ui->retryBox->itemData(i).value<int>())
            ui->retryBox->setCurrentIndex(i);
    }
    ui->retryBox->addItem(tr("infinite"), QVariant(-1));


    // populate the gain settings
    ui->gainBox->addItem(tr("25%"), QVariant(0.25f));
    ui->gainBox->addItem(tr("50%"), QVariant(0.50f));
    ui->gainBox->addItem(tr("75%"), QVariant(0.75f));
    ui->gainBox->addItem(tr("100%"), QVariant(1.0f));

    // restore the gain setting
    for (int i = 0; i < ui->gainBox->count(); i++)
    {
        if (settings.value(FC_AUDIO_GAINLABEL_KEY) == ui->gainBox->itemText(i))
            ui->gainBox->setCurrentIndex(i);
    }


    // populate the clock rates.
    ui->clockrateBox->addItem(tr("655Hz"), QVariant(655));
    ui->clockrateBox->addItem(tr("3000Hz"), QVariant(3000));

    // restore the clock rate setting
    for (int i = 0; i < ui->clockrateBox->count(); i++)
        if (settings.value(FC_AUDIO_CLOCKRATE_KEY) == ui->clockrateBox->itemData(i).value<int>())
            ui->clockrateBox->setCurrentIndex(i);

    // restore the callsign and password
    ui->callsign->setText(settings.value(FC_AUTH_CALLSIGN_KEY).toString());
    ui->password->setText(settings.value(FC_AUTH_PASSWORD_KEY).toString());
}

void FCPreferences::savePreferences()
{
    QSettings settings;

    // save the output device info
    int idx = ui->outputDevice->currentIndex();
    QAudioDeviceInfo deviceInfo = ui->outputDevice->itemData(idx).value<QAudioDeviceInfo>();
    settings.setValue(FC_AUDIO_DEVICE_KEY, deviceInfo.deviceName());

    // save the sample rate
    idx = ui->sampleRate->currentIndex();
    QString s = ui->sampleRate->itemText(idx);
    settings.setValue(FC_AUDIO_SAMPLERATE_KEY, QVariant(s));

    // save the gain
    idx = ui->gainBox->currentIndex();
    settings.setValue(FC_AUDIO_GAIN_KEY, QVariant(ui->gainBox->itemData(idx).value<float>()));
    settings.setValue(FC_AUDIO_GAINLABEL_KEY, QVariant(ui->gainBox->itemText(idx)));

    // save the clockrate
    idx = ui->clockrateBox->currentIndex();
    int bitrate = ui->clockrateBox->itemData(idx).value<int>();
    settings.setValue(FC_AUDIO_CLOCKRATE_KEY, QVariant(bitrate));

    // save the confirmation checkbox state
    settings.setValue(FC_GENERAL_CONFIRM_SEND_KEY, QVariant(ui->confirmCheckBox->isChecked()));

    // save the nretries combo
    idx = ui->retryBox->currentIndex();
    settings.setValue(FC_GENERAL_NRETRIES_KEY, QVariant(ui->retryBox->itemData(idx).value<int>()));

    // save the callsign and password
    settings.setValue(FC_AUTH_CALLSIGN_KEY, QVariant(ui->callsign->text()));
    settings.setValue(FC_AUTH_PASSWORD_KEY, QVariant(ui->password->text()));
}

void FCPreferences::on_outputDevice_activated(int idx)
{
    QSettings settings;
    QAudioDeviceInfo deviceInfo = ui->outputDevice->itemData(idx).value<QAudioDeviceInfo>();

    QList<int> sampleRates = deviceInfo.supportedSampleRates();
    qSort(sampleRates.begin(), sampleRates.end());

    ui->sampleRate->clear();
    for (int i = 0; i < sampleRates.size(); i++)
    {
        QString rate = QString("%1").arg(sampleRates.at(i));
        ui->sampleRate->addItem(rate);

        // look in the preferences for which rate to select
        if (rate == settings.value(FC_AUDIO_SAMPLERATE_KEY).toString())
            ui->sampleRate->setCurrentIndex(i);
    }
}

void FCPreferences::on_sampleRate_activated(int index)
{
    qDebug("sample rate changed to: %d", index);
}

void FCPreferences::on_volumeSlider_valueChanged(int value)
{
    qDebug("volume level changed to: %d", value);
}

//************************************* added for vertion 0.6 **********************
void FCPreferences::on_InvBox_stateChanged(int arg1)
{
    QSettings settings;
    //
    qDebug("Invert Box state changed to: %d",arg1);
    settings.setValue(FC_AUDIO_INVERT_KEY,QVariant(arg1));   //save check box state

}
//**********************************************************************************
