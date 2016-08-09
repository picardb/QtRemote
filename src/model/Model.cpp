#include "Model.h"

Model::Model(QObject *parent)
	: QObject(parent),
      m_dnsRegistrar(this),
      m_logger(this)
{
    /* Forward children signals */
    connect(&m_logger, SIGNAL(entryAdded(const QString&)),
            this, SIGNAL(logEntryAdded(const QString&)));

    /* Connect logging signals */
    connect(&m_dnsRegistrar, SIGNAL(added(const QString&)),
            this, SLOT(onDnsRegistrarAdded(const QString&)));
    connect(&m_dnsRegistrar, SIGNAL(error(const QString&)),
            this, SLOT(onDnsRegistrarError(const QString&)));
}

void Model::onDnsRegistrarAdded(const QString &msg)
{
    m_logger.addEntry(msg);
}

void Model::onDnsRegistrarError(const QString &msg)
{
    m_logger.addEntry(msg);
}

