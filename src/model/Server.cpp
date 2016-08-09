/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Server.h"


/*
 * Server::Server
 *
 * Server constructor.
 *
 * Parameters:
 *  - pDnsRegistrar: pointer to the DnsRegistrar instance
 *  - parent: pointer to the QObject parent (optional)
 */
Server::Server(DnsServiceRegistrar *pDnsRegistrar, QObject *parent)
    : QTcpServer(parent),
      m_pDnsRegistrar(pDnsRegistrar)
{

}


/*
 * Server::start
 *
 * Starts listening on the specified address/port pair and registers a new DNS service.
 *
 * Parameters:
 *  - address: address to listen on (optional, listens on every interfaces if empty)
 *  - port: port to listen on (optional, chooses a port automatically if empty)
 *
 * Return value: none
 */
void Server::start(const QHostAddress &address, quint16 port)
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
            emit started(port);
            m_dnsRef = m_pDnsRegistrar->add(SERVICE_TYPE, port);
        }
    }
}


/*
 * Server::stop
 *
 * Stops listening. Also un-registers the DNS service.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Server::stop() {
    if (!isListening()) {
        /* TODO: do something with this situation */
    } else {
        close();
        if (m_dnsRef != NULL) {
            m_pDnsRegistrar->remove(m_dnsRef);
        }
        emit stopped();
    }
}
