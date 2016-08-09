#pragma once

#include <QWidget>
#include "../model/Model.h"

class MainWidget : public QWidget
{
private:
    Model   *m_pModel;

public:
    MainWidget(Model *pModel, QWidget *parent = 0);
};
