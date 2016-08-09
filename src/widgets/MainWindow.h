/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QMainWindow>

#include "../model/Model.h"


/* MainWindow class
 *
 * Main window of the application.
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
    Model   *m_pModel;

public:
    MainWindow(Model *pModel, QWidget *parent = 0);
};
