/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../model/Model.h"

/*
 * SetupWidget class
 *
 * Contains server configuration and start/stop control.
 */
class SetupWidget : public QWidget
{
    Q_OBJECT

private:
    const int   PORT_EDIT_WIDTH = 50;
    const int   START_STOP_BUTTON_WIDTH = 70;

    Model   *m_pModel;
    bool    m_isStarted;

    QLineEdit   *m_pPortEdit;
    QPushButton *m_pStartStopButton;

    void setStartedControls();
    void setStoppedControls();

public:
    SetupWidget(Model *pModel, QWidget *parent = 0);

private slots:
    void onServerStarted();
    void onServerStopped();
    void onStartStopButtonClicked();
};
