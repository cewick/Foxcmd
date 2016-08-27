#ifndef FCLOG_H
#define FCLOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class FCLog;
}

class FCLog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FCLog(QWidget *parent = 0);
    ~FCLog();

    void log(const char *message, ...);
    
private:
    void refreshLogWindow();

    Ui::FCLog *ui;
};

#endif // FCLOG_H
