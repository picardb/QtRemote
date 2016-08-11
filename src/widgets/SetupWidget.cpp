/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "SetupWidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>


/*
 * SetupWidget::SetupWidget
 *
 * SetupWidget constructor. Creates and lays out the children widgets.
 *
 * Parameters:
 *  - pModel: pointer to the application model
 *  - parent: pointer to the parent widget (optional)
 */
SetupWidget::SetupWidget(Model *pModel, QWidget *parent)
    : QWidget(parent),
      m_pModel(pModel),
      m_isStarted(false)
{
    /* Create layouts */
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    QGridLayout *pBoxLayout = new QGridLayout;

    /* Create children widgets */
    QGroupBox *pSetupBox = new QGroupBox;
    QLabel *pPortLabel = new QLabel("Port number (0=auto):");
    pBoxLayout->addWidget(pPortLabel, 0, 0);
    m_pPortEdit = new QLineEdit;
    m_pPortEdit->setText("0");
    m_pPortEdit->setFixedWidth(PORT_EDIT_WIDTH);
    pBoxLayout->addWidget(m_pPortEdit, 0, 1);
    m_pStartStopButton = new QPushButton;
    m_pStartStopButton->setFixedWidth(START_STOP_BUTTON_WIDTH);
    connect(m_pStartStopButton, SIGNAL(clicked(bool)),
            this, SLOT(onStartStopButtonClicked()));
    pBoxLayout->addWidget(m_pStartStopButton, 1, 0, 1, 2, Qt::AlignCenter);
    pSetupBox->setLayout(pBoxLayout);
    pSetupBox->setTitle("Setup");
    pMainLayout->addWidget(pSetupBox);

    /* Connect model signals */
    connect(pModel, SIGNAL(serverStarted()),
            this, SLOT(onServerStarted()));
    connect(pModel, SIGNAL(serverStopped()),
            this, SLOT(onServerStopped()));

    /* Setup widget */
    setStoppedControls();
    setLayout(pMainLayout);
}


/*
 * SetupWidget::setStartedControls
 *
 * Sets the different controls properties when the server is stopped.
 *
 * Parameters: none
 *
 * Return value: none
 */
void SetupWidget::setStartedControls() {
    m_pStartStopButton->setText("Stop");
    m_pPortEdit->setEnabled(false);
}


/*
 * SetupWidget::setStoppedControls
 *
 * Sets the different controls properties when the server is started.
 *
 * Parameters: none
 *
 * Return value: none
 */
void SetupWidget::setStoppedControls() {
    m_pStartStopButton->setText("Start");
    m_pPortEdit->setEnabled(true);
}


/*
 * SetupWidget::onServerStarted
 *
 * Slot called when the server is started.
 *
 * Parameters: none
 * Return value: none
 */
void SetupWidget::onServerStarted() {
    m_isStarted = true;
    setStartedControls();
}


/*
 * SetupWidget::onServerStopped
 *
 * Slot called when the server is stopped.
 *
 * Parameters: none
 * Return value: none
 */
void SetupWidget::onServerStopped() {
    m_isStarted = false;
    setStoppedControls();
}


/*
 * SetupWidget::onStartStopButtonClicked
 *
 * Slot called when the start/stop button is clicked.
 *
 * Parameters: none
 * Return value: none
 */
void SetupWidget::onStartStopButtonClicked() {
    if (m_isStarted) {
        m_pModel->serverStop();
    }
    else {
        /* Get port number from the edit */
        quint16 port = m_pPortEdit->text().toUInt();
        m_pModel->serverStart(QHostAddress::Any, port);
    }
}
