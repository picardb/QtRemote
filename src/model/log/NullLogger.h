/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "Logger.h"

/*
 * NullLogger class
 *
 * Null implementation of the logging service.
 */
class NullLogger : public Logger
{
public:
    NullLogger(QObject *parent = 0) : Logger(parent) { /* Do nothing */ }

    virtual void addEntry(LogLevel , const QString &) { /* Do nothing */ }
};

