#pragma once
#include <vector>
#include "Domain.h"
class Repository
{
	private:
	std::vector<Researcher*> researchers;
	std::vector<Idea*> ideas;
	public:
		Repository() { readResearchersFromFile();  
		readIdeasFromFile(); }
		void addResearcher(Researcher *r) { researchers.push_back(r); }
		void addIdea(Idea *i) { ideas.push_back(i); }
		std::vector<Researcher*> getResearchers() { return researchers; }
		std::vector<Idea*> getIdeas() { return ideas; }
		~Repository() {}
		void readResearchersFromFile();
		void readIdeasFromFile();

		void saveAccepted();
		void sortIdeas();
};
