/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QTcpServer>
#include "DnsServiceRegistrar.h"

class Network : public QTcpServer
{
    Q_OBJECT

private:
    DnsServiceRegistrar     m_registrar;
    DNSServiceRef           m_dnsRef;
    QList<QTcpSocket*>      m_clientList;

    static const QString    SERVICE_TYPE;

public:
    Network(QObject *parent = 0);

    void startServer(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void stopServer();

signals:
    serverStarted();
    serverStopped();

private slots:
    void onTcpNewConnection();
    void onTcpDisconnection();
};
