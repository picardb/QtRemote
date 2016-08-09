/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Model.h"


/*
 * Model::Model
 *
 * Model constructor.
 *
 * Parameters:
 *	- parent: pointer to the QObject parent (optional)
 */
Model::Model(QObject *parent)
	: QObject(parent),
      m_dnsRegistrar(this),
      m_server(&m_dnsRegistrar, this),
      m_logger(this)
{
    /* Forward children signals */
    connect(&m_logger, SIGNAL(entryAdded(const QString&)),
            this, SIGNAL(logEntryAdded(const QString&)));
    connect(&m_server, SIGNAL(started(quint16)),
            this, SIGNAL(serverStarted()));
    connect(&m_server, SIGNAL(stopped()),
            this, SIGNAL(serverStopped()));

    /* Connect logging signals */
    connect(&m_dnsRegistrar, SIGNAL(added(const QString&)),
            this, SLOT(onDnsRegistrarAdded(const QString&)));
    connect(&m_dnsRegistrar, SIGNAL(removed(const QString&)),
            this, SLOT(onDnsRegistrarRemoved(const QString&)));
    connect(&m_dnsRegistrar, SIGNAL(error(const QString&)),
            this, SLOT(onDnsRegistrarError(const QString&)));
    connect(&m_server, SIGNAL(started(quint16)),
            this, SLOT(onServerStarted(quint16)));
    connect(&m_server, SIGNAL(stopped()),
            this, SLOT(onServerStopped()));
}


/*
 * Model::onDnsRegistrarAdded
 *
 * Slot called when a service has been registered with the DnsRegistrar.
 *
 * Parameters:
 *	- msg: message sent by the DnsRegistrar. Contains the domain, type and name of the new service
 *
 * Return value: none
 */
void Model::onDnsRegistrarAdded(const QString &msg)
{
    m_logger.addEntry(msg);
}


/*
 * Model::onDnsRegistrarRemoved
 *
 * Slot called when a service has been un-registered with the DnsRegistrar.
 *
 * Parameters:
 *  - msg: message sent by the DnsRegistrar
 *
 * Return value: none
 */
void Model::onDnsRegistrarRemoved(const QString &msg)
{
    m_logger.addEntry(msg);
}


/*
 * Model::onDnsRegistrarError
 *
 * Slot called when the DnsRegistrar reports an error.
 *
 * Parameters:
 *	- msg: error message sent by the DnsRegistrar
 *
 * Return value: none
 */
void Model::onDnsRegistrarError(const QString &msg)
{
    m_logger.addEntry(msg);
}


/*
 * Model::onServerStarted
 *
 * Slot called when the server has been started.
 *
 * Parameters:
 *	- port: port number on which the server is listening
 *
 * Return value: none
 */
void Model::onServerStarted(quint16 port)
{
    m_logger.addEntry(QString("Server started on port %1").arg(port));
}


/*
 * Model::onServerStopped
 *
 * Slot called when the server has been stopped.
 *
 * Parameters: none
 *
 * Return value: none
 */
void Model::onServerStopped()
{
    m_logger.addEntry("Server stopped");
}

