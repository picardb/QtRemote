/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Logger.h"

#include <QDateTime>


/*
 * Logger::Logger
 *
 * Logger constructor.
 *
 * Parameters:
 *	- parent: pointer to the QObject parent (optional)
 */
Logger::Logger(QObject *parent)
    : QObject(parent)
{

}


/*
 * Logger::addEntry
 *
 * Adds a new entry to the log.
 *
 * Parameters:
 *	- msg: message to log
 *
 * Return value: none
 */
void Logger::addEntry(const QString &msg)
{
    /* Get current time in string format */
    QString timeStr(QDateTime::currentDateTime().toString("[hh:mm::ss]"));
    emit entryAdded(QString("%1 %2").arg(timeStr, msg));
}
