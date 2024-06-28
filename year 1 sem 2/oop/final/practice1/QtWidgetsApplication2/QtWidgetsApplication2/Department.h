#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Department
{
private:
	string name;
	string description;
	int nrWords = 0;
	int nrVolunteers = 0;
public:
	Department(string n, string d) :name{ n }, description{ d } { this->setNumberWords(); }
	void setNrVolunteers(int nr) { nrVolunteers = nr; }
	int getNrVolunteers() { return nrVolunteers; }
	void setNumberWords() {
		istringstream ss(description);
		string a;
		while (getline(ss, a, ' ')) {
			nrWords++;
		}
	}
	int getNrWords() { return this->nrWords; }
	~Department() {}
	string getName() { return this->name; }
	string getDescription() { return this->description; }
};
