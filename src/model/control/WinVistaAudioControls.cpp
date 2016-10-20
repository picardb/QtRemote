/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "WinVistaAudioControls.h"

#include <windows.h>
#include <mmdeviceapi.h>
#include "model/Model.h"


/*
 * WinVistaAudioControls::WinVistaAudioControls
 *
 * WinVistaAudioControls constructor. Retrieves the windows endpoint volume.
 *
 * Parameters: none
 */
WinVistaAudioControls::WinVistaAudioControls()
    : m_pEndpointVolume(NULL)
{
    /* Get windows audio endpoint */
    if (!getAudioEndpoint()) {
        Model::logger().addEntry(Logger::Error, QString("Cannot get the audio endpoint"));
    }
}


/*
 * WinVistaAudioControls::getAudioEndpoint
 *
 * Gets the audio enpoint using Windows API.
 *
 * Parameters: none
 *
 * Return value: operation success (true/false)
 */
bool WinVistaAudioControls::getAudioEndpoint() {
    HRESULT hr;

    /* Init COM library */
    CoInitialize(NULL);

    /* Get device */
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    if (hr != S_OK) {
        return false;
    }
    IMMDevice *defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    if (hr != S_OK) {
        return false;
    }
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    /* Get endpoint */
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&m_pEndpointVolume);
    if (hr != S_OK) {
        return false;
    }
    defaultDevice->Release();
    defaultDevice = NULL;

    /* Check the endpoint */
    if (m_pEndpointVolume == NULL) {
        return false;
    }
    else {
        return true;
    }
}


/*
 * WinVistaAudioControls::processRequest
 *
 * Processes an audio request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void WinVistaAudioControls::processRequest(const Request &request) {
    switch (request.command) {
    case CMD_ID_RAISE_VOL:
        raiseVolume(request);
        break;

    case CMD_ID_LOWER_VOL:
        lowerVolume(request);
        break;

    case CMD_ID_SET_VOL:
        setVolume(request);
        break;

    case CMD_ID_MUTE_VOL:
        muteVolume(request);
        break;

    default:
        Model::logger().addEntry(Logger::Error, QString("Error in audio request: command ID is invalid (%1)").arg(request.command));
    }
}


/*
 * WinVistaAudioControls::raiseVolume
 *
 * Processes a raise volume request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void WinVistaAudioControls::raiseVolume(const Request &request) {
    /* Get percentage from the data */
    if (request.length != 1 || request.data.size() != 1) {
        Model::logger().addEntry(Logger::Error, QString("Error while trying to process audio request: request length is invalid"));
        return;
    }
    unsigned char percentage = request.data[0];

    /* Raise volume */
    float volume;
    m_pEndpointVolume->GetMasterVolumeLevelScalar(&volume);
    volume += (float)percentage/100.0;
    if (volume > 1.0) {
        volume = 1.0;
    }
    unsigned int channelCount;
    m_pEndpointVolume->GetChannelCount(&channelCount);
    for (unsigned int i = 0 ; i < channelCount ; i++) {
        m_pEndpointVolume->SetChannelVolumeLevelScalar(i, volume, NULL);
    }
}


/*
 * WinVistaAudioControls::lowerVolume
 *
 * Processes a lower volume request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void WinVistaAudioControls::lowerVolume(const Request &request) {
    /* Get percentage from the data */
    if (request.length != 1 || request.data.size() != 1) {
        Model::logger().addEntry(Logger::Error, QString("Error in LowerVolume request: request length is invalid"));
        return;
    }
    unsigned char percentage = request.data[0];

    /* Lower volume */
    float volume;
    m_pEndpointVolume->GetMasterVolumeLevelScalar(&volume);
    volume -= (float)percentage/100.0;
    if (volume < 0.0) {
        volume = 0.0;
    }
    unsigned int channelCount;
    m_pEndpointVolume->GetChannelCount(&channelCount);
    for (unsigned int i = 0 ; i < channelCount ; i++) {
        m_pEndpointVolume->SetChannelVolumeLevelScalar(i, volume, NULL);
    }
}


/*
 * WinVistaAudioControls::setVolume
 *
 * Processes a set volume request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void WinVistaAudioControls::setVolume(const Request &request) {
    /* Get volume from the data */
    if (request.length != 1 || request.data.size() != 1) {
        Model::logger().addEntry(Logger::Error, QString("Error in SetVolume request: request length is invalid"));
        return;
    }
    unsigned char percentage = request.data[0];

    /* Check the percentage value */
    if (percentage > 100) {
        Model::logger().addEntry(Logger::Error, QString("Error in SetVolume request: volume parameter is invalid"));
        return;
    }

    /* Set volume */
    float volume = (float)percentage / 100.0;
    unsigned int channelCount;
    m_pEndpointVolume->GetChannelCount(&channelCount);
    for (unsigned int i = 0 ; i < channelCount ; i++) {
        m_pEndpointVolume->SetChannelVolumeLevelScalar(i, volume, NULL);
    }
}


/*
 * WinVistaAudioControls::muteVolume
 *
 * Processes a mute/unmute volume request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void WinVistaAudioControls::muteVolume(const Request &request) {
    /* Set volume mute status */
    BOOL isMuted;
    m_pEndpointVolume->GetMute(&isMuted);
    m_pEndpointVolume->SetMute(!isMuted, NULL);
}
