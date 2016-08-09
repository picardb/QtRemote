#pragma once

#include <QObject>

#include "DnsServiceRegistrar.h"
#include "Logger.h"

class Model : public QObject
{
	Q_OBJECT

private:
	DnsServiceRegistrar	m_dnsRegistrar;
    Logger              m_logger;

public:
	Model(QObject *parent = 0);

    DNSServiceRef dnsRegistrarAdd(const QString& type, quint16 port, const QString& name = "") { return m_dnsRegistrar.add(type, port, name); }
    void dnsRegistrarRemove(DNSServiceRef ref) { m_dnsRegistrar.remove(ref); }

signals:
    logEntryAdded(const QString& );

private slots:
    void onDnsRegistrarAdded(const QString& msg);
    void onDnsRegistrarError(const QString& msg);
};
