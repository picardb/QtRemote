/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "SettingsDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include "globals.h"


/*
 * SettingsDialog::SettingsDialog
 *
 * SettingsDialog constructor. Creates and lays out the children widgets.
 *
 * Parameters:
 *  - parent: pointer to the parent widget (optional)
 *  - f: window flags (optional)
 */
SettingsDialog::SettingsDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    /* Create layout */
    QVBoxLayout *pMainLayout = new QVBoxLayout;

    /* Create log directory edit */
    QHBoxLayout *pLogLayout = new QHBoxLayout;
    QLabel *pLogDirLabel = new QLabel("Log directory: ");
    pLogLayout->addWidget(pLogDirLabel);
    m_pLogDirEdit = new QLineEdit;
    m_pLogDirEdit->setText(g_appSettings.value("LOG_DIR").toString());
    pLogLayout->addWidget(m_pLogDirEdit);
    m_pLogBrowseButton = new QPushButton("Browse");
    connect(m_pLogBrowseButton, SIGNAL(clicked(bool)),
            this, SLOT(onLogBrowseButtonClicked()));
    pLogLayout->addWidget(m_pLogBrowseButton);
    pMainLayout->addLayout(pLogLayout);

    /* Create OK/Cancel buttons */
    QHBoxLayout *pButtonsLayout = new QHBoxLayout;
    m_pOkButton = new QPushButton("OK");
    m_pOkButton->setDefault(true);
    pButtonsLayout->addWidget(m_pOkButton, 0, Qt::AlignRight);
    connect(m_pOkButton, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
    m_pCancelButton = new QPushButton("Cancel");
    pButtonsLayout->addWidget(m_pCancelButton, 0, Qt::AlignLeft);
    connect(m_pCancelButton, SIGNAL(clicked(bool)),
            this, SLOT(reject()));
    pMainLayout->addLayout(pButtonsLayout);

    /* Setup dialog */
    setLayout(pMainLayout);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Settings");
}


/*
 * SettingsDialog::onLogBrowseButtonClicked
 *
 * Slot called when the log directory "Browse" button is clicked.
 *
 * Parameters: none
 *
 * Return value: none
 */
void SettingsDialog::onLogBrowseButtonClicked() {
    /* Create a file dialog */
    QString newDir = QFileDialog::getExistingDirectory(this, "Select a results directory", m_pLogDirEdit->text());

    if (newDir != "") {
        m_pLogDirEdit->setText(newDir);
    }
}

