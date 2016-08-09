#include "LogWidget.h"

#include <QVBoxLayout>
#include <QGroupBox>

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
    connect(pModel, SIGNAL(logEntryAdded(const QString&)),
            this, SLOT(onLogEntryAdded(const QString&)));
    pBoxLayout->addWidget(m_pLogEdit);
    pLogBox->setLayout(pBoxLayout);
    pMainLayout->addWidget(pLogBox);

    /* Setup widget */
    setLayout(pMainLayout);
}

void LogWidget::onLogEntryAdded(const QString &msg)
{
    m_pLogEdit->append(msg);
}
