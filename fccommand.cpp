#include "fccommand.h"

FCCommand::FCCommand(const QString &desc, QList<uint> command) :
    QObject(0)
{
    this->m_desc = desc;
    this->m_command = command;
}

