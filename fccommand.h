#ifndef FCCOMMAND_H
#define FCCOMMAND_H

#include <QObject>

class FCCommand : public QObject
{
    Q_OBJECT;

public:
    FCCommand(const QString &desc, QList<uint> command);

    QString m_desc;
    QList<uint> m_command;
};


#endif // FCCOMMAND_H
