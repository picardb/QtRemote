#include "DnsServiceRegistrar.h"

#include <QSocketNotifier>

DnsServiceRegistrar::DnsServiceRegistrar(QObject *parent)
	: QObject(parent)
{

}

DNSServiceRef DnsServiceRegistrar::add(const QString& type, quint16 port, const QString& name)
{
    /* Deal with name default value */
    char *nameStr;
    if (name == "") {
        nameStr = NULL;
    } else {
        nameStr = name.toUtf8().data();
    }

    /* Create and register the new service ref. */
    DNSServiceRef ref;
    DNSServiceErrorType err = DNSServiceRegister(&ref, 0, 0, nameStr, type.toUtf8().data(), NULL, NULL, port, 0,
                                                 NULL, registerCallback, this);
    if (err != kDNSServiceErr_NoError) {
        emit error(QString("Error while registering service (error code = %1)").arg(err));
        return NULL;
    }

    /* Create the QSocketNotifier */
    int sockFd = DNSServiceRefSockFD(ref);
    RefNotifier *pNotif = new RefNotifier(ref, sockFd, QSocketNotifier::Read, this);
    connect(pNotif, SIGNAL(activated(int)), this, SLOT(onNotifierActivated(int)));

    return ref;
}

void DnsServiceRegistrar::remove(DNSServiceRef ref)
{
    if(m_serviceList.contains(ref)) {
        DNSServiceRefDeallocate(ref);
        m_serviceList.removeAll(ref);
    }
}

void DnsServiceRegistrar::onNotifierActivated(int)
{
    RefNotifier *pNotif = static_cast<RefNotifier*>(sender());
    DNSServiceProcessResult(pNotif->ref());
    pNotif->deleteLater();
}

void DnsServiceRegistrar::registerCallback(DNSServiceRef ref, DNSServiceFlags flags, DNSServiceErrorType errorCode,
                                           const char *name, const char *regtype, const char *domain, void *context)
{
    DnsServiceRegistrar *pRegistrar = static_cast<DnsServiceRegistrar*>(context);

    if (errorCode != kDNSServiceErr_NoError) {
        emit pRegistrar->error(QString("Error while registering service (error code = %1)").arg(errorCode));
        return;
    }
    else {
        if(flags & kDNSServiceFlagsAdd) {
            emit pRegistrar->added(QString("New DNS Service registered (name = %1, type = %2, domain = %3)")
                                   .arg(QString::fromUtf8(name), QString::fromUtf8(regtype), QString::fromUtf8(domain)));
        }
        pRegistrar->m_serviceList.append(ref);
    }
}
