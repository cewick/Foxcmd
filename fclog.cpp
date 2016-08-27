#include "fclog.h"
#include "ui_fclog.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>

FCLog::FCLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCLog)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);

    refreshLogWindow();
}

FCLog::~FCLog()
{
    delete ui;
}

void FCLog::log(const char *message, ...)
{
#define BUFSIZE 500
    char buf[BUFSIZE];
    va_list ap;

    va_start(ap, message);
    vsnprintf(buf, BUFSIZE, message, ap);
    va_end(ap);

    QString msg(buf);
    QDateTime date;
    QFile file("foxcom.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream stream(&file);

    msg.prepend(" - ");
    msg.prepend(date.currentDateTimeUtc().toString());

    stream << msg << flush;

    refreshLogWindow();
}

void FCLog::refreshLogWindow()
{
    QFile file("foxcom.log");
    file.open(QIODevice::ReadOnly);

    QTextStream stream(&file);

    ui->textEdit->setPlainText(stream.readAll());
}
