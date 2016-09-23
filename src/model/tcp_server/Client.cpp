/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Client.h"

#include "Request.h"
#include "model/Model.h"

/*
 * Client::Client
 *
 * Client constructor.
 *
 * Parameters:
 *	- pSocket: pointer to the QTcpSocket created when the server accepted the
 * new connection
 */
Client::Client(QTcpSocket *pSocket)
    : m_pSocket(pSocket)
{
    /* Setup TCP socket */
    connect(m_pSocket, SIGNAL(disconnected()),
            this, SIGNAL(disconnected()));
    connect(m_pSocket, SIGNAL(readyRead()),
            this, SLOT(onTcpReadyRead()));

    /* Setup timeout timer */
    m_timeoutTimer.setSingleShot(true);
    connect(&m_timeoutTimer, SIGNAL(timeout()),
            this, SLOT(onRequestTimeout()));
}

/*
 * Client::~Client
 *
 * Client destructor. Deletes the client socket.
 */
Client::~Client() {
    delete m_pSocket;
}

/*
 * Client::isRequestComplete
 *
 * Checks if there is a complete request in the buffer.
 *
 * Parameters: none
 *
 * Return value: true if there is a complete request, false otherwise
 */
bool Client::isRequestComplete() {
    /* If buffer size < 4, request header is incomplete */
    if (m_requestBuffer.size() < 4) {
        return false;
    }

    /* Otherwise, check data length */
    int dataLength = m_requestBuffer[2] * 256 + m_requestBuffer[3];
    if (m_requestBuffer.size() < 4 + dataLength) {
        return false;
    } else {
        return true;
    }
}

/*
 * Client::processRequest
 *
 * Processes a request from the buffer. Make sure a request is complete
 * before calling that function.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Client::processRequest() {
    /* Create request object */
    Request req;
    req.system = m_requestBuffer[0];
    req.command = m_requestBuffer[1];
    req.length = m_requestBuffer[2] * 256 + m_requestBuffer[3];
    req.data = m_requestBuffer.mid(4, req.length);

    /* Send to control */
    Model::control().processRequest(req);

    /* Remove request from buffer */
    m_requestBuffer.remove(0, 4 + req.length);
}

/*
 * Client::onTcpReadyRead
 *
 * Slot called when data is available on the socket. Appends the data to the
 * request buffer and processes all complete requests.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Client::onTcpReadyRead() {
    /* If the timeout timer is running, stop it */
    if (m_timeoutTimer.isActive()) {
        m_timeoutTimer.stop();
    }

    /* Copy incoming data in the buffer */
    m_requestBuffer.append(m_pSocket->readAll());

    /* Process complete requests */
    while (isRequestComplete()) {
        processRequest();
    }

    /* If the buffer is not empty, start the timeout timer */
    if (!m_requestBuffer.isEmpty()) {
        m_timeoutTimer.start(REQUEST_TIMEOUT_MSEC);
    }
}

/*
 * Client::onRequestTimeout
 *
 * Slot called when the timeout buffer fires. Clears all data from the request
 * buffer.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Client::onRequestTimeout() {
    /* Empty the request buffer */
    m_requestBuffer.clear();
}
