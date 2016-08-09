#include "Server.h"

Server::Server(DnsServiceRegistrar *pDnsRegistrar, QObject *parent)
    : QTcpServer(parent),
      m_pDnsRegistrar(pDnsRegistrar)
{

}

void Server::start(const QHostAddress &address, quint16 port)
{
    if (isListening()) {
        /* TODO: do something with this situation */
    }
    else {
        bool result = QTcpServer::listen(address, port);
        if (!result) {
            /* TODO: do something with the error */
            return;
        } else {
            quint16 port = serverPort();
            emit started(port);
            m_pDnsRegistrar->add("_toto._tcp", port);
        }
    }
}
