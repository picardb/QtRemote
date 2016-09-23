/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Control.h"

#include "model/Model.h"

/*
 * Control::processRequest
 *
 * Processes a request from a client. Dispatches the request to the adequate
 * sub-system.
 *
 * Parameters:
 *  - request: request information (header + data)
 *
 * Return value: none
 */
void Control::processRequest(const Request &request) {
    switch (request.system) {
    case SYSTEM_ID_AUDIO:
        m_audio.processRequest(request);
        break;

    default:
        Model::logger().addEntry(Logger::Error, QString("Error while trying to process request: invalid system ID (%1)").arg((request.system)));
    }
}
