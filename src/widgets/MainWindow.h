#pragma once

#include <QMainWindow>

#include "../model/Model.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
    Model   *m_pModel;

public:
    MainWindow(Model *pModel, QWidget *parent = 0);
	~MainWindow();
};
