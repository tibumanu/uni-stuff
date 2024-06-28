#include "QtWidgetsApplicationExam.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // initialise repo, service and model
    Repository repo;
    Service service(repo);
    TableModel model(service);
    // for each researcher, open a window
    for (auto researcher : service.getResearchers())
    {
		QtWidgetsApplicationExam* window = new QtWidgetsApplicationExam(&service, researcher, &model);
		window->show();
	}
    return a.exec();
}
