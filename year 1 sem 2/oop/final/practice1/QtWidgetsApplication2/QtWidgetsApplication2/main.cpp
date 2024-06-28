#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service serv;
    // for each department, create a widget
    for (Department* dep : serv.getDepartments()) {
		asdf* w = new asdf{ dep, serv };
		w->show();
	}
    return a.exec();
}
