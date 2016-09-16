/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Network.h"
#include "model/Model.h"
#include <QTcpSocket>

/*
 * Constants definitions
 */
const QString Network::SERVICE_TYPE = "_qtremote._tcp";

Network::Network(QObject *parent)
    : QTcpServer(parent),
      m_registrar(this)
{
    /* Connect TCP server signals */
    connect(this, SIGNAL(newConnection()),
            this, SLOT(onTcpNewConnection()));

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


/*
 * Network::onTcpNewConnection
 *
 * Called when the TCP server notifies a new connection. Accepts the connection
 * and adds the client to the client list.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Network::onTcpNewConnection() {
    /* Accept connection */
    QTcpSocket *clientConnection = nextPendingConnection();

    /* Add client to the list */
    if (clientConnection != 0) {
        connect(clientConnection, SIGNAL(disconnected()),
                this, SLOT(onTcpDisconnection()));
        m_clientList.append(clientConnection);
        Model::logger().addEntry(Logger::Info, "New connection from " + clientConnection->peerAddress().toString());
    }
}


/*
 * Network::onTcpDisconnection
 *
 * Called when a client notifies its disconnection. Removes the client from the list
 * and deletes the corresponding socket.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Network::onTcpDisconnection() {
    /* Remove client from the list */
    QTcpSocket *clientConnection = static_cast<QTcpSocket*>(sender());
    m_clientList.removeAll(clientConnection);

    /* Log info */
    Model::logger().addEntry(Logger::Info, "Connection closed from" + clientConnection->peerAddress().toString());

    /* Delete the client */
    clientConnection->deleteLater();
}
