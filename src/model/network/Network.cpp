/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Network.h"
#include "model/Model.h"

/*
 * Constants definitions
 */
const QString Network::SERVICE_TYPE = "_qtremote._tcp";

Network::Network(QObject *parent)
    : QTcpServer(parent),
      m_registrar(this)
{

}

/*
 * Network::startServer
 *
 * Starts listening on the specified address/port pair and registers a new DNS service.
 *
 * Parameters:
 *  - address: address to listen on (optional, listens on every interfaces if empty)
 *  - port: port to listen on (optional, chooses a port automatically if empty)
 *
 * Return value: none
 */
void Network::startServer(const QHostAddress &address, quint16 port)
{
    if (isListening()) {
        /* TODO: do something with this situation */
    }
    else {
        bool result = listen(address, port);
        if (!result) {
            /* TODO: do something with the error */
            return;
        } else {
            quint16 port = serverPort();
            emit serverStarted();
            Model::logger().addEntry(Logger::Info, QString("Server started on port %1").arg(port));
            m_dnsRef = m_registrar.add(SERVICE_TYPE, port);
        }
    }
}


/*
 * Network::stopServer
 *
 * Stops listening. Also un-registers the DNS service.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Network::stopServer() {
    if (!isListening()) {
        /* TODO: do something with this situation */
    } else {
        close();
        if (m_dnsRef != NULL) {
            m_registrar.remove(m_dnsRef);
        }
        emit serverStopped();
        Model::logger().addEntry(Logger::Info, "Server stopped");
    }
}
