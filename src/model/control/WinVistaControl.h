/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "Control.h"
#include "WinVistaAudioControls.h"


/*
 * WinVistaControl class
 *
 * Implementation of the control interface for Windows Vista and superior.
 */
class WinVistaControl : public Control
{
private:
    static const unsigned char  SYSTEM_ID_AUDIO = 1;

    WinVistaAudioControls   m_audio;

public:
    WinVistaControl(QObject *parent = 0);

    virtual void processRequest(const Request& request);
};
