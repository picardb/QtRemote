/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QMainWindow>


/* MainWindow class
 *
 * Main window of the application.
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
    void createMenuBar();

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void onSettingsMenuClicked();
};
