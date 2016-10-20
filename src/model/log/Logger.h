/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QObject>
#include <QString>


/*
 * Logger class
 *
 * Interface for the logging service.
 */
class Logger : public QObject
{
    Q_OBJECT

public:
    enum LogLevel { Info, Warning, Error, Debug };

    Logger(QObject *parent = 0) : QObject(parent) { /* Do nothing */ }

    virtual void addEntry(LogLevel lvl, const QString &msg) = 0;

signals:
    entryAdded(const QString& );
};
