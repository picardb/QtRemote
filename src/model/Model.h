#pragma once

#include <QObject>

#include "DnsServiceRegistrar.h"
#include "Server.h"
#include "Logger.h"

class Model : public QObject
{
	Q_OBJECT

private:
	DnsServiceRegistrar	m_dnsRegistrar;
    Server              m_server;
    Logger              m_logger;

public:
	Model(QObject *parent = 0);

    DNSServiceRef dnsRegistrarAdd(const QString& type, quint16 port, const QString& name = "") { return m_dnsRegistrar.add(type, port, name); }
    void dnsRegistrarRemove(DNSServiceRef ref) { m_dnsRegistrar.remove(ref); }
    void serverStart(const QHostAddress &address = QHostAddress::Any, quint16 port = 0) { m_server.start(address, port); }

signals:
    logEntryAdded(const QString& );

private slots:
    void onDnsRegistrarAdded(const QString& msg);
    void onDnsRegistrarError(const QString& msg);
    void onServerStarted(quint16 port);
};
