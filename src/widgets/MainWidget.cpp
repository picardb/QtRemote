/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "MainWidget.h"

#include <QGridLayout>
#include <QSpacerItem>
#include "LogWidget.h"
#include "SetupWidget.h"


/*
 * MainWidget::MainWidget
 *
 * MainWidget constructor. Creates and lays out the children widgets.
 *
 * Parameters:
 *  - pModel: pointer to the application model
 *  - parent: pointer to the parent widget (optional)
 */
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    /* Create layout */
    QGridLayout *pMainLayout = new QGridLayout;

    /* Create children widgets */
    SetupWidget *pSetupWidget = new SetupWidget;
    pMainLayout->addWidget(pSetupWidget, 0, 0);
    LogWidget *pLogWidget = new LogWidget;
    pMainLayout->addWidget(pLogWidget, 0, 1, 2, 1);
    pMainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 1, 0);
    pMainLayout->setColumnStretch(1, 1);

    /* Setup widget */
    setLayout(pMainLayout);
}
