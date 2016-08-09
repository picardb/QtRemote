/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QTcpServer>
#include "DnsServiceRegistrar.h"

/*
 * Server class
 *
 * Manages the network stuff.
 */
class Server : public QTcpServer
{
    Q_OBJECT

private:
    DnsServiceRegistrar *m_pDnsRegistrar;
    DNSServiceRef       m_dnsRef;

    const QString       SERVICE_TYPE = "_qtremote._tcp";

public:
    Server(DnsServiceRegistrar *pDnsRegistrar, QObject *parent = 0);

    void start(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void stop();

signals:
    started(quint16 port);
    stopped();
};
