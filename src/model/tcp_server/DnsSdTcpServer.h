/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "TcpServer.h"
#include <QTcpServer>
#include "DnsServiceRegistrar.h"
#include "Client.h"


/*
 * DnsSdTcpServer class
 *
 * Implementation of the TCP Server using DNS_SD library for service registration.
 * Accepts incoming connections and creates Clients.
 */
class DnsSdTcpServer : public TcpServer
{
    Q_OBJECT

private:
    QTcpServer              m_server;
    DnsServiceRegistrar     m_registrar;
    DNSServiceRef           m_dnsRef;
    QList<Client*>          m_clientList;

    static const QString    SERVICE_TYPE;

public:
    DnsSdTcpServer(QObject *parent = 0);

    virtual void startServer(const QHostAddress &address, quint16 port);
    virtual void stopServer();

private slots:
    void onClientConnection();
    void onClientDisconnection();
};
