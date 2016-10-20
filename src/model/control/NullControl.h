/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "Control.h"

class NullControl : public Control
{
public:
    NullControl(QObject *parent = 0) : Control(parent) { /* Do nothing */ }

    virtual void processRequest(const Request& ) { /* Do nothing */ }
};

