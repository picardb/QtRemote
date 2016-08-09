#include <QApplication>
#include "widgets/MainWindow.h"
#include "model/Model.h"

int main(int argc, char *argv[])
{
	/* Create application */
	QApplication a(argc, argv);

	/* Create model */
	Model m;

	/* Create main window */
    MainWindow w(&m);
	w.show();
    m.dnsRegistrarAdd("_toto._tcp", 12000);
    m.dnsRegistrarAdd("_toto2._tcp", 12000, "TOTO2");

	/* Start */
	return a.exec();
}
