/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QTcpServer>
#include "DnsServiceRegistrar.h"
/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Client.h"

/*
 * TcpServer class
 *
 * TCP server. Accepts incoming connections and creates Clients.
 */
class TcpServer : public QTcpServer
{
    Q_OBJECT

private:
    DnsServiceRegistrar     m_registrar;
    DNSServiceRef           m_dnsRef;
    QList<Client*>          m_clientList;

    static const QString    SERVICE_TYPE;

public:
    TcpServer(QObject *parent = 0);

    void startServer(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void stopServer();

signals:
    serverStarted();
    serverStopped();

private slots:
    void onClientConnection();
    void onClientDisconnection();
};
