/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "MainWindow.h"

#include "MainWidget.h"


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
    /* Create central widget */
    MainWidget *pCentralWidget = new MainWidget;
    setCentralWidget(pCentralWidget);

    /* Setup window */
    setWindowTitle("Qt Remote");
}
