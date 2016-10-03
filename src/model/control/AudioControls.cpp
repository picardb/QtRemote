/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "AudioControls.h"

#include <windows.h>
#include <mmdeviceapi.h>
#include "model/Model.h"

/*
 * AudioControls::AudioControls
 *
 * AudioControls constructor. Retrieves the windows endpoint volume.
 *
 * Parameters: none
 */
AudioControls::AudioControls()
    : m_pEndpointVolume(NULL)
{
    /* Get windows audio endpoint volume */
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&m_pEndpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;
}

/*
 * AudioControls::processRequest
 *
 * Processes an audio request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void AudioControls::processRequest(const Request &request) {
    switch (request.command) {
    case CMD_ID_RAISE_VOL:
        raiseVolume(request);
        break;

    case CMD_ID_LOWER_VOL:
        lowerVolume(request);
        break;

    default:
        Model::logger().addEntry(Logger::Error, QString("Error while trying to process audio request: invalid command ID (%1)").arg(request.command));
    }
}

/*
 * AudioControls::raiseVolume
 *
 * Processes a raise volume request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void AudioControls::raiseVolume(const Request &request) {
    /* Get percentage from the data */
    if (request.length < 1 || request.data.size() < 1) {
        Model::logger().addEntry(Logger::Error, QString("Error while trying to process audio request: invalid request length"));
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
    for (int i = 0 ; i < channelCount ; i++) {
        m_pEndpointVolume->SetChannelVolumeLevelScalar(i, volume, NULL);
    }
}

/*
 * AudioControls::lowerVolume
 *
 * Processes a lower volume request.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void AudioControls::lowerVolume(const Request &request) {
    /* Get percentage from the data */
    if (request.length < 1 || request.data.size() < 1) {
        Model::logger().addEntry(Logger::Error, QString("Error while trying to process audio request: invalid request length"));
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
    for (int i = 0 ; i < channelCount ; i++) {
        m_pEndpointVolume->SetChannelVolumeLevelScalar(i, volume, NULL);
    }
}
