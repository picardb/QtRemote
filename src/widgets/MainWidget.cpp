#include "MainWidget.h"

#include <QHBoxLayout>
#include "LogWidget.h"

MainWidget::MainWidget(Model *pModel, QWidget *parent)
    : QWidget(parent),
      m_pModel(pModel)
{
    /* Create layout */
    QHBoxLayout *pMainLayout = new QHBoxLayout;

    /* Create children widgets */
    LogWidget *pLogWidget = new LogWidget(pModel);
    pMainLayout->addWidget(pLogWidget);

    /* Setup widget */
    setLayout(pMainLayout);
}

void MainWidget::showEvent(QShowEvent *event)
{
    m_pModel->serverStart();
}
