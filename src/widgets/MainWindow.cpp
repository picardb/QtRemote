/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "MainWindow.h"

#include <QMenuBar>
#include "MainWidget.h"
#include "SettingsDialog.h"
#include "globals.h"


/*
 * MainWindow::MainWindow
 *
 * MainWindow constructor. Creates the central widget and sets up the window properties.
 *
 * Parameters:
 *  - pModel: pointer to the application model
 *  - parent: pointer to the parent widget (optional)
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* Create menu bar */
    createMenuBar();

    /* Create central widget */
    MainWidget *pCentralWidget = new MainWidget;
    setCentralWidget(pCentralWidget);

    /* Setup window */
    setWindowTitle("Qt Remote");
}


/*
 * MainWindow::createMenuBar
 *
 * Creates the main window menu bar and all its actions.
 *
 * Parameters: none
 *
 * Return value: none
 */
void MainWindow::createMenuBar() {
    QMenu *pFileMenu = menuBar()->addMenu("File");
    pFileMenu->addAction("Settings", this, SLOT(onSettingsMenuClicked()));
}


/*
 * MainWindow::onSettingsMenuClicked
 *
 * Slot called chen the Settings menu is clicked. Displays the settings dialog.
 *
 * Parameters: none
 *
 * Return value: none
 */
void MainWindow::onSettingsMenuClicked() {
    SettingsDialog settingsDialog(this);

    /* Show the dialog */
    if (settingsDialog.exec() == QDialog::Accepted) {
        /* Retrieve the settings values */
        g_appSettings.setValue("LOG_DIR", settingsDialog.getLogDir());
    }
}
