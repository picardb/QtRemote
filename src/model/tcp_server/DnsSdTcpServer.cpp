/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "DnsSdTcpServer.h"

#include "model/Model.h"

/*
 * Constants definitions
 */
const QString DnsSdTcpServer::SERVICE_TYPE = "_qtremote._tcp";


/*
 * DnsSdTcpServer::DnsSdTcpServer
 *
 * DnsSdTcpServer constructor.
 *
 * Parameters:
 *	- parent: pointer to the QObject parent (optional)
 */
DnsSdTcpServer::DnsSdTcpServer(QObject *parent)
    : TcpServer(parent),
      m_server(),
      m_registrar(this)
{
    /* Connect TCP server signals */
    connect(&m_server, SIGNAL(newConnection()),
            this, SLOT(onClientConnection()));
}


/*
 * DnsSdTcpServer::startServer
 *
 * Starts listening on the specified address/port pair and registers a new DNS service.
 *
 * Parameters:
 *  - address: address to listen on (optional, listens on every interfaces if empty)
 *  - port: port to listen on (optional, chooses a port automatically if empty)
 *
 * Return value: none
 */
void DnsSdTcpServer::startServer(const QHostAddress &address, quint16 port)
{
    if (m_server.isListening()) {
        /* TODO: do something with this situation */
    }
    else {
        bool result = m_server.listen(address, port);
        if (!result) {
            /* TODO: do something with the error */
            return;
        } else {
            quint16 port = m_server.serverPort();
            emit serverStarted();
            Model::logger().addEntry(Logger::Info, QString("Server started on port %1").arg(port));
            m_dnsRef = m_registrar.add(SERVICE_TYPE, port);
        }
    }
}


/*
 * DnsSdTcpServer::stopServer
 *
 * Stops listening. Also un-registers the DNS service.
 *
 * Parameters: none
 *
 * Return value: none
 */
void DnsSdTcpServer::stopServer() {
    if (!m_server.isListening()) {
        /* TODO: do something with this situation */
    } else {
        m_server.close();
        if (m_dnsRef != NULL) {
            m_registrar.remove(m_dnsRef);
        }
        emit serverStopped();
        Model::logger().addEntry(Logger::Info, "Server stopped");
    }
}


/*
 * DnsSdTcpServer::onClientConnection
 *
 * Called when the TCP server notifies a new connection. Accepts the connection
 * and adds the client to the client list.
 *
 * Parameters: none
 *
 * Return value: none
 */
void DnsSdTcpServer::onClientConnection() {
    /* Accept connection */
    QTcpSocket *pClientSocket = m_server.nextPendingConnection();

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
 * DnsSdTcpServer::onClientDisconnection
 *
 * Called when a client notifies its disconnection. Removes the client from the list
 * and deletes it.
 *
 * Parameters: none
 *
 * Return value: none
 */
void DnsSdTcpServer::onClientDisconnection() {
    Client *pClient = static_cast<Client*>(sender());

    /* Log info */
    Model::logger().addEntry(Logger::Info, "Connection closed from" + pClient->ipAddress());

    /* Remove client from the list */
    m_clientList.removeAll(pClient);

    /* Delete the client */
    pClient->deleteLater();
}

