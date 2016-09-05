/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QObject>
#include <QString>


/*
 * Logger class
 *
 * Manages the application log.
 */
class Logger : public QObject
{
    Q_OBJECT

public:
    enum LogLevel { Info, Warning, Error, Debug };

    Logger(QObject *parent = 0);

    void addEntry(LogLevel lvl, const QString& msg);

signals:
    entryAdded(const QString& );
};
