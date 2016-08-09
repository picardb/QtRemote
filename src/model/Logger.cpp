#include "Logger.h"

#include <QDateTime>

Logger::Logger(QObject *parent)
    : QObject(parent)
{

}

void Logger::addEntry(const QString &msg)
{
    /* Get current time in string format */
    QString timeStr(QDateTime::currentDateTime().toString("[hh:mm::ss]"));
    emit entryAdded(QString("%1 %2").arg(timeStr, msg));
}
