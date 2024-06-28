#pragma once
#include <string>
class Researcher
{
private:
	std::string name;
	std::string position;
public:
	Researcher(std::string name, std::string position): name(name), position(position) {}
	std::string getName() { return name; }
	std::string getPosition() { return position; }
};

class Idea {
private:
		std::string title;
		std::string description;
		std::string status;
		std::string creator;
		int duration;

public:
	Idea(std::string title, std::string description, std::string status, std::string creator, int duration): title(title), description(description), status(status), creator(creator), duration(duration) {}
	std::string getTitle() { return title; }
	std::string getDescription() { return description; }
	std::string getStatus() { return status; }
	std::string getCreator() { return creator; }
	int getDuration() { return duration; }
	void setStatus(std::string newStatus) { status = newStatus; }

};

