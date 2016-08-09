#include "Logger.h"

Logger::Logger(QObject *parent)
    : QObject(parent)
{

}

void Logger::addEntry(const QString &str)
{
    emit entryAdded(str);
}
