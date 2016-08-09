/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QWidget>
#include "../model/Model.h"


/*
 * MainWidget class
 *
 * Main widget of the application. Acts as the central widget of the MainWindow.
 */
class MainWidget : public QWidget
{
private:
    Model   *m_pModel;

public:
    MainWidget(Model *pModel, QWidget *parent = 0);
};
