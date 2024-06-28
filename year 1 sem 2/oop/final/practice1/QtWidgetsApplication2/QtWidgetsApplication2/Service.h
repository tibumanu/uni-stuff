#pragma once
#include "Repository.h"
#include "Observer.h"
class Service : public Subject
{
private:
	Repository repository;
public:
	Service() {}
	~Service() {}

	vector<Department*> getDepartments() { return this->repository.getDepartments(); }
	vector<Department*> getDepartmentsSorted() {
		vector<Department*> deps = this->repository.getDepartments();
		sort(deps.begin(), deps.end(), [](Department* a, Department* b) { return a->getNrVolunteers() < b->getNrVolunteers(); });
		return  deps;
	}
	vector<Volunteer*> getVolunteers() {
		return this->repository.getVolunteers();
	}
	vector<Volunteer*> getVolunteerByDepartment(Department* dep) {
		vector<Volunteer*> volunteers;
		for (Volunteer* vol : this->repository.getVolunteers()) {
			if (vol->getDepartment() == dep->getName() || vol->getDepartment() == "unassigned") {
				volunteers.push_back(vol);
			}
		}
		sort(volunteers.begin(), volunteers.end(), [](Volunteer* a, Volunteer* b) {return a->getName() < b->getName(); });
		return volunteers;
	}
	void assignVolunteer(string mail, Department* dep);
	void addVolunteer(string name, string email, string interests) {
		vector<string> listInter;
		istringstream ss(interests);
		string inter;
		while (getline(ss, inter, ',')) {
			listInter.push_back(inter);
		}
		Volunteer* volunteer = new Volunteer(name, email, listInter);
		this->repository.addVolunteer(volunteer);
		//this->notify();
	}
	vector<Volunteer*> getSuitableVolunteers(Department* dep);

	void setNrVolunteers();
};
