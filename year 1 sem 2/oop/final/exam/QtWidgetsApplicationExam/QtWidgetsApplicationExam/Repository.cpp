#include "Repository.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

void Repository::readResearchersFromFile()
{
	// use tokenize
	std::ifstream file("researchers.txt");
	std::string line;
	while (getline(file, line))
	{
		std::vector<std::string> tokens = tokenize(line, '|');
		if (tokens.size() != 2)
			continue;
		std::string name = tokens[0];
		std::string position = tokens[1];
		Researcher *r = new Researcher(name, position);
		researchers.push_back(r);
	}
	file.close();
}

void Repository::readIdeasFromFile()
{
	std::ifstream file("ideas.txt");
	std::string line;
	while (getline(file, line))
	{
		std::vector<std::string> tokens = tokenize(line, '|');
		if (tokens.size() != 5)
			continue;
		std::string title = tokens[0];
		std::string description = tokens[1];
		std::string status = tokens[2];
		std::string creator = tokens[3];
		int duration = stoi(tokens[4]);
		Idea *i = new Idea(title, description, status, creator, duration);
		ideas.push_back(i);
	}
	file.close();
}

void Repository::saveAccepted()
{	
	std::sort(ideas.begin(), ideas.end(), [](Idea* i1, Idea* i2) {
		return i1->getDuration() > i2->getDuration();
	});
	std::ofstream file("accepted.txt");
	for (auto i : ideas)
	{
		if (i->getStatus() == "accepted")
		{
			file << i->getTitle() << ": " << i->getDescription() << " (by " << i->getCreator() << "), taking " << i->getDuration() << "y\n";
		}
	}
}

void Repository::sortIdeas()
{
	std::sort(ideas.begin(), ideas.end(), [](Idea* i1, Idea* i2) {
		return i1->getDuration() > i2->getDuration();
	});
}
