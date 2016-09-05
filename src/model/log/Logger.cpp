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
 *  - lvl: log level (debug, error, ...)
 *	- msg: message to log
 *
 * Return value: none
 */
void Logger::addEntry(LogLevel lvl, const QString &msg)
{
    /* Get current time in string format */
    QString timeStr(QDateTime::currentDateTime().toString("[hh:mm::ss]"));

    /* Add log level */
    QString lvlStr;
    switch (lvl) {
    case Info:
        lvlStr = "[INFO ]";
        break;

    case Warning:
        lvlStr = "[WARN ]";
        break;

    case Error:
        lvlStr = "[ERROR]";
        break;

    case Debug:
        lvlStr = "[DEBUG]";
        break;

    default:
        lvlStr = "[ ??? ]";
        break;
    }

    emit entryAdded(QString("%1 %2 %3").arg(timeStr, lvlStr, msg));
}
