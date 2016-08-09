#include "MainWindow.h"

#include "MainWidget.h"

MainWindow::MainWindow(Model *pModel, QWidget *parent)
    : QMainWindow(parent),
      m_pModel(pModel)
{
    /* Create central widget */
    MainWidget *pCentralWidget = new MainWidget(pModel);
    setCentralWidget(pCentralWidget);

    /* Setup window */
    setWindowTitle("Qt Remote");
}

MainWindow::~MainWindow()
{

}
