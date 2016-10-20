/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QObject>
#include "model/tcp_server/Request.h"


/*
 * Control class
 *
 * Interface for the control service.
 */
class Control : public QObject
{
public:
    Control(QObject *parent = 0) : QObject(parent) { /* Do nothing */ }

    virtual void processRequest(const Request& request) = 0;
};
