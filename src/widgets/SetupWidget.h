/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

/*
 * SetupWidget class
 *
 * Contains server configuration and start/stop control.
 */
class SetupWidget : public QWidget
{
    Q_OBJECT

private:
    static const int   PORT_EDIT_WIDTH = 50;
    static const int   START_STOP_BUTTON_WIDTH = 70;

    bool    m_isStarted;

    QLineEdit   *m_pPortEdit;
    QPushButton *m_pStartStopButton;

    void setStartedControls();
    void setStoppedControls();

public:
    SetupWidget(QWidget *parent = 0);

private slots:
    void onServerStarted();
    void onServerStopped();
    void onStartStopButtonClicked();
};
