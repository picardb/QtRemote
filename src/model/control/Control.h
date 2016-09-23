/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "AudioControls.h"
#include "model/tcp_server/Request.h"

/*
 * Control class
 *
 * Processes all control requests.
 */
class Control
{
private:
    static const unsigned char  SYSTEM_ID_AUDIO = 1;

    AudioControls   m_audio;

public:
    void processRequest(const Request& request);
};
