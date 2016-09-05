/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QObject>
#include <QVector>
#include <QSocketNotifier>
#include "dns_sd.h"

/*
 * RefNotifier class
 *
 * Helper class only used to associate a DNSServiceRef with a QSocketNotifier.
 */
class RefNotifier : public QSocketNotifier
{
private:
    DNSServiceRef   m_ref;

public:
    RefNotifier(DNSServiceRef ref, qintptr socket, Type type, QObject *parent)
        : QSocketNotifier(socket, type, parent), m_ref(ref) {}

    DNSServiceRef ref() const { return m_ref; }
};

/*
 * DnsServiceRegistrar class
 *
 * This class allows the registration of several DNS services.
 */
class DnsServiceRegistrar : public QObject
{
	Q_OBJECT

private:
    QVector<DNSServiceRef>	m_serviceList;

    static void DNSSD_API registerCallback(DNSServiceRef ref, DNSServiceFlags flags, DNSServiceErrorType errorCode,
                                           const char *name, const char *regtype, const char *domain, void *context);

public:
	DnsServiceRegistrar(QObject *parent = 0);

    DNSServiceRef add(const QString& type, quint16 port, const QString& name = QString(""));
    void remove(DNSServiceRef ref);

private slots:
     void onNotifierActivated();
};
