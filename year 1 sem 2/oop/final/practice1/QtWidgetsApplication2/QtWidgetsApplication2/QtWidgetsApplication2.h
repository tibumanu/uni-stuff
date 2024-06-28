#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets>

#include <QMessageBox>
#include <QListWidget>
#include "Observer.h"
#include "Service.h"
#include <QVBoxLayout>
class asdf : public QWidget, public Observer
{
    Q_OBJECT

public:
    asdf(Department* dep, Service& serv, QWidget* parent = nullptr);
    ~asdf() {
        delete assignedList;
        delete unassignedList;
        delete addVolunteerButton;
        delete assignButton;
        delete name;
        delete email;
        delete interests;
        delete topThreeBox;
    }
    void update() override;
    void connect();
    void populateList();
    //void topVolunteersUnassigned(bool acc);
    //void populateTop();
    void addVolunteer();
    void assignVolunteer();
private:
    /*
    This will be the window for the department. It will contain a list of volunteers assigned to the department and a list of unassigned volunteers.
    Volunteers can be selected and assigned to the department.
    Volunteers can be "created" as well, by adding their name, email and interests. They will be, by default, unassigned.
    */
    // layout for everything:
    QVBoxLayout* layout;
    QListWidget* assignedList;
    QListWidget* unassignedList;
    QPushButton* addVolunteerButton;
    QPushButton* assignButton;
    // fields for adding a volunteer
    QLineEdit* name;
    QLineEdit* email;
    QLineEdit* interests;
    QCheckBox* topThreeBox;
    // when the above is checked, the top 3 volunteers will be displayed in the unassigned list
    Service& service;
    Department* department;
    bool topVol = false;
    QWidget* addVolWidget = new QWidget();
};