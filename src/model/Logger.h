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
    Logger(QObject *parent = 0);

    void addEntry(const QString& msg);

signals:
    entryAdded(const QString& );
};
