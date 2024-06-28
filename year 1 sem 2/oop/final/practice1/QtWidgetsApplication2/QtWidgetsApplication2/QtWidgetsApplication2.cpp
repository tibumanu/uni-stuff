#include "QtWidgetsApplication2.h"
#include <QtWidgets>
asdf::asdf(Department* dep, Service& serv, QWidget* parent) : QWidget(parent), department{ dep }, service{ serv }{
    this->layout = new QVBoxLayout{ this };
    this->assignedList = new QListWidget{};
    this->unassignedList = new QListWidget{};
    this->addVolunteerButton = new QPushButton{ "Add Volunteer" };
    this->assignButton = new QPushButton{ "Assign Volunteer" };
    this->name = new QLineEdit{};
    this->email = new QLineEdit{};
    this->interests = new QLineEdit{};
    this->topThreeBox = new QCheckBox{ "Top 3 volunteers" };
    this->layout->addWidget(this->assignedList);
    this->layout->addWidget(this->unassignedList);
    this->layout->addWidget(this->addVolunteerButton);
    this->layout->addWidget(this->assignButton);
    this->layout->addWidget(this->name);
    this->layout->addWidget(this->email);
    this->layout->addWidget(this->interests);
    this->layout->addWidget(this->topThreeBox);
    this->service.addObserver(this);
    populateList();
    connect();
}

void asdf::update()
{
    populateList();
}

void asdf::connect()
{
    QObject::connect(this->addVolunteerButton, &QPushButton::clicked, this, &asdf::addVolunteer);
	QObject::connect(this->assignButton, &QPushButton::clicked, this, &asdf::assignVolunteer);
    QObject::connect(this->topThreeBox, &QCheckBox::stateChanged, this, [this]() {
		this->topVol = !this->topVol;
		populateList();
		});
}

void asdf::populateList()
{
    // populate both lists
    this->assignedList->clear();
    this->unassignedList->clear();
    for (Volunteer* vol : this->service.getVolunteerByDepartment(this->department)) {
        if (vol->getDepartment() == this->department->getName()) {
			this->assignedList->addItem(QString::fromStdString(vol->getName()));
		}
        else {
			this->unassignedList->addItem(QString::fromStdString(vol->getName()));
		}
	}


}


void asdf::assignVolunteer()
{
	// get the selected volunteer, and its email
    // the selected volunteer displays only the name
    // we need to get the email from the service
    // volunteers are unique by email; not ordered
    
    // get the selected volunteer, his name, and search for his email
    string name = this->unassignedList->selectedItems().at(0)->text().toStdString();
    string email;
    for (Volunteer* vol : this->service.getVolunteers()) {
        if (vol->getName() == name) {
			email = vol->getEmail();
			break;
		}
	}
    // assign the volunteer
	this->service.assignVolunteer(email, this->department);


	// notify the observers
	this->service.notify();
	populateList();
}
void asdf::addVolunteer()
{
    // get the data from the fields
    string name = this->name->text().toStdString();
    string email = this->email->text().toStdString();
    string interests = this->interests->text().toStdString();
    // add the volunteer
    this->service.addVolunteer(name, email, interests);
    // notify the observers
    this->service.notify();
    update();

}
