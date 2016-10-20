/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include <QApplication>
#include "globals.h"
#include "constants.h"
#include "widgets/MainWindow.h"
#include "model/Model.h"

/* Model services */
#include "model/log/FileLogger.h"
#include "model/tcp_server/DnsSdTcpServer.h"
#include "model/control/WinVistaControl.h"


/*
 * Global variables definitions.
 */
QSettings g_appSettings(INI_FILE_PATH, QSettings::IniFormat);


/*
 * createDefaultSettings
 *
 * Creates default values for the program settings if they do not exist in the ini file.
 *
 * Parameters: none
 *
 * Return value: none
 */
void createDefaultSettings() {
    if (!g_appSettings.contains("LOG_DIR")) {
        g_appSettings.setValue("LOG_DIR", DEFAULT_LOG_DIR);
    }
}


/*
 * main
 *
 * Entry point of the application.
 *
 * Parameters:
 *  - argc: number of arguments
 *  - argv: array containing the program arguments
 */
int main(int argc, char *argv[])
{
    /* Create model services */
    FileLogger fileLogger;
    Model::provideLogger(&fileLogger);
    DnsSdTcpServer dnsSdServer;
    Model::provideTcpServer(&dnsSdServer);
    WinVistaControl winVistaControl;
    Model::provideControl(&winVistaControl);

	/* Create application */
    QApplication a(argc, argv);
    createDefaultSettings();

	/* Create main window */
    MainWindow w;
    w.show();

	/* Start */
	return a.exec();
}
