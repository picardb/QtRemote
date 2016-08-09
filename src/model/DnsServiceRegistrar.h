#pragma once

#include <QObject>
#include <QVector>
#include <QSocketNotifier>
#include "dns_sd.h"

class RefNotifier : public QSocketNotifier
{
private:
    DNSServiceRef   m_ref;

public:
    RefNotifier(DNSServiceRef ref, qintptr socket, Type type, QObject *parent)
        : m_ref(ref), QSocketNotifier(socket, type, parent) {}

    DNSServiceRef ref() const { return m_ref; }
};

class DnsServiceRegistrar : public QObject
{
	Q_OBJECT

private:
    QVector<DNSServiceRef>	m_serviceList;
    DNSServiceRef           m_tempRef;

    static void DNSSD_API registerCallback(DNSServiceRef ref, DNSServiceFlags flags, DNSServiceErrorType errorCode,
                                           const char *name, const char *regtype, const char *domain, void *context);

public:
	DnsServiceRegistrar(QObject *parent = 0);

    DNSServiceRef add(const QString& type, quint16 port, const QString& name = QString(""));
    void remove(DNSServiceRef ref);

private slots:
    void onNotifierActivated(int );

signals:
    void error(const QString& );
    void added(const QString& );
    void removed();
};
