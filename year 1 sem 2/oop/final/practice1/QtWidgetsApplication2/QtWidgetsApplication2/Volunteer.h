#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Volunteer
{
private:
	string name;
	string email;
	string department;
	vector<string> listInterests;
public:
	Volunteer(string n, string e, vector<string>elems, string d = "unassigned") : name{ n }, email{ e }, department{ d }, listInterests{ elems } {}
	~Volunteer() {}

	string getName() { return this->name; }
	string getEmail() { return this->email; }
	string getDepartment() { return this->department; }
	vector<string> getInterests() { return this->listInterests; }
	void setDepartment(string dep) { this->department = dep; }
	string toFile() {
		string ss = this->name + ";" + this->email + ";" + this->department + ";";
		for (int i = 0; i < listInterests.size(); i++) {
			ss += listInterests[i];
			if (i < listInterests.size() - 1) {
				ss += ",";
			}
		}
		return ss += "\n";
	}

	string toString() {
		string ss = this->name + " " + this->email + " ";
		for (int i = 0; i < listInterests.size(); i++) {
			ss += listInterests[i];
			if (i < listInterests.size() - 1) {
				ss += ",";
			}
		}
		return ss;
	}
};
