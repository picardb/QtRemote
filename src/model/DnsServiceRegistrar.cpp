/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "DnsServiceRegistrar.h"

#include <QSocketNotifier>
#include <QtEndian>


/*
 * DnsServiceRegistrar::DnsServiceRegistrar
 *
 * DnsServiceRegistrar constructor.
 *
 * Parameters:
 *	- parent: pointer to the parent QObject (optional)
 */
DnsServiceRegistrar::DnsServiceRegistrar(QObject *parent)
	: QObject(parent)
{

}


/*
 * DnsServiceRegistrar::add
 *
 * Registers a new service.
 *
 * Parameters:
 *	- type: service type
 *	- port: port number of the registered service
 *	- name: service name (optional)
 *
 * Return value: reference of the DNS service if registration was successful, NULL otherwise
 */
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
     DNSServiceErrorType err = DNSServiceRegister(&ref, 0, 0, nameStr, type.toUtf8().data(), NULL,
                                                                 NULL, qToBigEndian(port), 0, NULL, registerCallback, this);
    if (err != kDNSServiceErr_NoError) {
        emit error(QString("Error while registering service (error code = %1)").arg(err));
        return NULL;
    }

    /* Create the QSocketNotifier */
    int sockFd = DNSServiceRefSockFD(ref);
    RefNotifier *pNotif = new RefNotifier(ref, sockFd, QSocketNotifier::Read, this);
     connect(pNotif, SIGNAL(activated(int)), this, SLOT(onNotifierActivated()));

    return ref;
}


/*
 * DnsServiceRegistrar::remove
 *
 * Un-registers a DNS service and removes it from the list.
 *
 * Parameters:
 *	- ref: reference of the service returned by DnsServiceRegistrar::add
 *
 * Return value: none
 */
void DnsServiceRegistrar::remove(DNSServiceRef ref)
{
    if(m_serviceList.contains(ref)) {
        DNSServiceRefDeallocate(ref);
        m_serviceList.removeAll(ref);
          emit removed("DNS Service un-registered");
    }
}


/*
 * DnsServiceRegistrar::registerCallback
 *
 * Callback function for DNSServiceRegister. Adds the registered service to the list.
 *
 * Parameters: see DNS-SD API documentation (DNSServiceRegisterReply)
 *
 * Return value: none
 */
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
                emit pRegistrar->added(QString("DNS Service registered (name = %1, type = %2, domain = %3)")
                                              .arg(QString::fromUtf8(name), QString::fromUtf8(regtype), QString::fromUtf8(domain)));
          }
          pRegistrar->m_serviceList.append(ref);
     }
}


/*
 * DnsServiceRegistrar::onNotifierActivated
 *
 * Slot called when a socket associated with a RefNotifier receives data. Calls DNSServiceProcessResult on
 * the associated DNS service reference. Deletes the RefNotifier afterwards.
 *
 * Parameters: none
 *
 * Return value: none
 */
void DnsServiceRegistrar::onNotifierActivated()
{
    RefNotifier *pNotif = static_cast<RefNotifier*>(sender());
    DNSServiceProcessResult(pNotif->ref());
    pNotif->deleteLater();
}
