/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <endpointvolume.h>
#include "model/tcp_server/Request.h"


/*
 * WinVistaAudioControls class
 *
 * Manages all Windows Vista (and superior) audio controls.
 */
class WinVistaAudioControls
{    
private:
    static const unsigned char CMD_ID_RAISE_VOL = 0x01;
    static const unsigned char CMD_ID_LOWER_VOL = 0x02;
    static const unsigned char CMD_ID_SET_VOL   = 0x03;
    static const unsigned char CMD_ID_MUTE_VOL  = 0x04;

    IAudioEndpointVolume    *m_pEndpointVolume;

    bool getAudioEndpoint();
    void raiseVolume(const Request& request);
    void lowerVolume(const Request& request);
    void setVolume(const Request& request);
    void muteVolume(const Request& request);

public:
    WinVistaAudioControls();

    void processRequest(const Request& request);
};
