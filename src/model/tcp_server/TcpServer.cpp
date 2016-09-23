/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "TcpServer.h"

#include "model/Model.h"

/*
 * Constants definitions
 */
const QString TcpServer::SERVICE_TYPE = "_qtremote._tcp";

/*
 * TcpServer::TcpServer
 *
 * TcpServer constructor.
 *
 * Parameters:
 *	- parent: pointer to the QObject parent (optional)
 */
TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent),
      m_registrar(this)
{
    /* Connect TCP server signals */
    connect(this, SIGNAL(newConnection()),
            this, SLOT(onClientConnection()));

}

/*
 * TcpServer::startServer
 *
 * Starts listening on the specified address/port pair and registers a new DNS service.
 *
 * Parameters:
 *  - address: address to listen on (optional, listens on every interfaces if empty)
 *  - port: port to listen on (optional, chooses a port automatically if empty)
 *
 * Return value: none
 */
void TcpServer::startServer(const QHostAddress &address, quint16 port)
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
 * TcpServer::stopServer
 *
 * Stops listening. Also un-registers the DNS service.
 *
 * Parameters: none
 *
 * Return value: none
 */
void TcpServer::stopServer() {
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
 * TcpServer::onClientConnection
 *
 * Called when the TCP server notifies a new connection. Accepts the connection
 * and adds the client to the client list.
 *
 * Parameters: none
 *
 * Return value: none
 */
void TcpServer::onClientConnection() {
    /* Accept connection */
    QTcpSocket *pClientSocket = nextPendingConnection();

    /* Create client */
    if (pClientSocket != 0) {
        Client *pClient = new Client(pClientSocket);
        connect(pClient, SIGNAL(disconnected()),
                this, SLOT(onClientDisconnection()));
        m_clientList.append(pClient);
        Model::logger().addEntry(Logger::Info, "New connection from " + pClient->ipAddress());
    }
}


/*
 * TcpServer::onClientDisconnection
 *
 * Called when a client notifies its disconnection. Removes the client from the list
 * and deletes it.
 *
 * Parameters: none
 *
 * Return value: none
 */
void TcpServer::onClientDisconnection() {
    Client *pClient = static_cast<Client*>(sender());

    /* Log info */
    Model::logger().addEntry(Logger::Info, "Connection closed from" + pClient->ipAddress());

    /* Remove client from the list */
    m_clientList.removeAll(pClient);

    /* Delete the client */
    pClient->deleteLater();
}
