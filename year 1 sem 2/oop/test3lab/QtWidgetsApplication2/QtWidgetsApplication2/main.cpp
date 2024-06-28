//#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Service.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service service(repo);
    GUI gui{ repo, service };
    gui.show();
    return a.exec();
}
