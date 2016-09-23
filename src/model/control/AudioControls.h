/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <endpointvolume.h>
#include "model/tcp_server/Request.h"

/*
 * AudioControls class
 *
 * Manages all windows audio controls.
 */
class AudioControls
{    
private:
    static const unsigned char CMD_ID_RAISE_VOL = 0x01;
    static const unsigned char CMD_ID_LOWER_VOL = 0x02;
    static const unsigned char CMD_ID_SET_VOL   = 0x03;

    IAudioEndpointVolume    *m_pEndpointVolume;

    void raiseVolume(const Request& request);
    void lowerVolume(const Request& request);

public:
    AudioControls();

    void processRequest(const Request& request);
};
