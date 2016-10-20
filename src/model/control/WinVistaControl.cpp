/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "WinVistaControl.h"

#include "model/Model.h"


/*
 * WinVistaControl::WinVistaControl
 *
 * WinVistaControl constructor.
 *
 * Parameters:
 *  - parent: pointer to the parent QObject (optional)
 */
WinVistaControl::WinVistaControl(QObject *parent)
    : Control(parent)
{

}


/*
 * WinVistaControl::processRequest
 *
 * Processes a request from a client. Dispatches the request to the adequate
 * sub-system.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void WinVistaControl::processRequest(const Request &request) {
    switch (request.system) {
    case SYSTEM_ID_AUDIO:
        m_audio.processRequest(request);
        break;

    default:
        Model::logger().addEntry(Logger::Error, QString("Error while trying to process request: invalid system ID (%1)").arg((request.system)));
    }
}
