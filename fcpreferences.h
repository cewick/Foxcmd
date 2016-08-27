#ifndef FCPREFERENCES_H
#define FCPREFERENCES_H

#include <QDialog>
//********************************************************************
//Register held (Windows) persistent (session to session) values
//Values in version 0.5
#define FC_AUDIO_DEVICE_KEY         "FC_AUDIO_DEVICE_KEY"
#define FC_AUDIO_SAMPLERATE_KEY     "FC_AUDIO_SAMPLERATE_KEY"
#define FC_AUDIO_GAIN_KEY           "FC_AUDIO_GAIN_KEY"
#define FC_AUDIO_GAINLABEL_KEY      "FC_AUDIO_GAINLABEL_KEY"
#define FC_AUDIO_CLOCKRATE_KEY      "FC_AUDIO_CLOCKRATE_KEY"

#define FC_GENERAL_CONFIRM_SEND_KEY "FC_GENERAL_CONFIRM_SEND_KEY"
#define FC_GENERAL_NRETRIES_KEY     "FC_GENERAL_NRETRIES_KEY"

#define FC_AUTH_CALLSIGN_KEY        "FC_AUTH_CALLSIGN_KEY"
#define FC_AUTH_PASSWORD_KEY        "FC_AUTH_PASSWORD_KEY"
//added value for version 0.6
#define FC_AUDIO_INVERT_KEY         "FC_AUDIO_INVERT_KEY"
//*********************************************************************

namespace Ui {
class FCPreferences;
}

class FCPreferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit FCPreferences(QWidget *parent = 0);
    ~FCPreferences();
    void savePreferences();
    int exec();

    
private slots:
    void on_outputDevice_activated(int index);

    void on_sampleRate_activated(int index);

    void on_volumeSlider_valueChanged(int value);
//****************************************************
//*change with version 0.6 add checkbox to invert audio pulses
    void on_InvBox_stateChanged(int arg1);

private:
    void populatePreferencesWindow();

    Ui::FCPreferences *ui;
};

#endif // FCPREFERENCES_H
