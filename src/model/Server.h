#pragma once

#include <QTcpServer>
#include "DnsServiceRegistrar.h"

class Server : public QTcpServer
{
    Q_OBJECT

private:
    DnsServiceRegistrar *m_pDnsRegistrar;
    DNSServiceRef       m_dnsRef;

public:
    Server(DnsServiceRegistrar *pDnsRegistrar, QObject *parent = 0);

    void start(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);

signals:
    void started(quint16 port);
};
