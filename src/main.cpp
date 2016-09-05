/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include <QApplication>
#include "widgets/MainWindow.h"
#include "model/Model.h"


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
	/* Create application */
    QApplication a(argc, argv);

	/* Create main window */
    MainWindow w;
    w.show();

	/* Start */
	return a.exec();
}
