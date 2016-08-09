/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "LogWidget.h"

#include <QVBoxLayout>
#include <QGroupBox>


/*
 * LogWidget::LogWidget
 *
 * LogWidget constructor. Creates and lays out the children widgets.
 *
 * Parameters:
 *  - pModel: pointer to the application model
 *  - parent: pointer to the parent widget (optional)
 */
LogWidget::LogWidget(Model *pModel, QWidget *parent)
    : QWidget(parent),
      m_pModel(pModel)
{
    /* Create layouts */
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    QVBoxLayout *pBoxLayout = new QVBoxLayout;

    /* Create children widgets */
    QGroupBox *pLogBox = new QGroupBox("Log");
    m_pLogEdit = new QTextEdit;
    m_pLogEdit->setReadOnly(true);
    pBoxLayout->addWidget(m_pLogEdit);
    pLogBox->setLayout(pBoxLayout);
    pMainLayout->addWidget(pLogBox);

    /* Connect model signals */
    connect(pModel, SIGNAL(logEntryAdded(const QString&)),
            this, SLOT(onLogEntryAdded(const QString&)));

    /* Setup widget */
    setLayout(pMainLayout);
}


/*
 * LogWidget::onLogEntryAdded
 *
 * Slot called when a new entry is created by the Logger.
 *
 * Parameters:
 *  - msg: message logged by the Logger
 *
 * Return value: none
 */
void LogWidget::onLogEntryAdded(const QString &msg)
{
    m_pLogEdit->append(msg);
}
