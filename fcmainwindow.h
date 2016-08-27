#ifndef FCMAINWINDOW_H
#define FCMAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QPushButton>
#include <QTimer>
#include <QIODevice>
#include <QGroupBox>

#include "fclog.h"
#include "fcpreferences.h"
#include "fcrig.h"
#include "fcencoder.h"
#include "fccommand.h"

typedef enum status_state
{
    FC_SENDING = 0,
    FC_IDLE,
    FC_ERROR
} status_state_t;


namespace Ui {
    class FCMainWindow;
}


class FCMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FCMainWindow(QWidget *parent = 0);
    ~FCMainWindow();

private:
    void sendCommand(FCCommand *);
    void makeCommandTable();
    void readPreferences();
    void writePreferences();
    void updateStatus(status_state_t);
    void layoutMainWindow();
    int getCurrentDevice(QAudioDeviceInfo& info);
    void cleanupAudio();
    quint8 calculate_address();

    Ui::FCMainWindow *m_ui;
    QList<FCCommand *> *m_commandTable;
    FCLog *m_logWindow;
    FCPreferences *m_preferencesWindow;
    FCRig *m_rig;
    QAudioOutput *m_audioOutput;
    FCEncoder *m_encoder;
    QPushButton *m_sendButton;
    QGroupBox *cBox;

private slots:
    void on_sendButton_clicked();
    void on_actionPreferences_triggered();
    void on_actionLog_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_FoxCom_triggered();
    void handleStateChanged(QAudio::State);

public slots:
    void on_aboutToQuit();
};

#endif // FCMAINWINDOW_H
