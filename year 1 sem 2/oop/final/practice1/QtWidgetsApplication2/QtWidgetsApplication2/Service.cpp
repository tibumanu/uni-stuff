#include "Service.h"
void Service::assignVolunteer(string mail, Department* dep)
{
	for (Volunteer* vol : this->repository.getVolunteers()) {
		if (vol->getEmail() == mail) {
			vol->setDepartment(dep->getName());
			break;
		}
	}
}
vector<Volunteer*> Service::getSuitableVolunteers(Department* dep)
{
	vector<Volunteer*> found;
	double scors[] = { -1.0,-1.0,-1.0 };
	Volunteer* vols[] = { NULL, NULL, NULL };
	for (Volunteer* vol : this->repository.getVolunteers()) {
		if (vol->getDepartment() != "unassigned") continue;
		vector<string> interests = vol->getInterests();
		double scores = 0.0;
		int count = 0;
		for (string word : interests) {
			istringstream ss(dep->getDescription());
			string t;
			while (getline(ss, t, ' ')) {
				if (t == word) count++;
			}
		}
		scores = (count * 1.0) / (dep->getNrWords() * 1.0);
		for (int i = 0; i < 3; ++i) {
			if (scores > scors[i]) {
				// Shift the lower scores down
				for (int j = 2; j > i; --j) {
					scors[j] = scors[j - 1];
					vols[j] = vols[j - 1];
				}
				// Insert the new score and volunteer
				scors[i] = scores;
				vols[i] = vol;
				break;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (vols[i] != NULL) found.push_back(vols[i]);
	}
	return found;
}

void Service::setNrVolunteers()
{
	for (Department* dep : this->repository.getDepartments()) {
		int count = 0;
		for (Volunteer* vol : this->repository.getVolunteers()) {
			if (vol->getDepartment() == dep->getName()) count++;
		}
		dep->setNrVolunteers(count);
	}
}