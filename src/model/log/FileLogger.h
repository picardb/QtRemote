/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "Logger.h"

/*
 * FileLogger class
 *
 * Implementation of the logging service that logs all entries in dated files.
 */
class FileLogger : public Logger
{
public:
    FileLogger(QObject *parent = 0);

    virtual void addEntry(LogLevel lvl, const QString &msg);
};
