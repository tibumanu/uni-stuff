#pragma once
#include "Repository.h"
class Service
{
	private:
		Repository repo;
	public:
		Service(Repository r) : repo(r) {
			repo.sortIdeas();
		}
		void addResearcher(Researcher* r) { repo.addResearcher(r); }
		void addIdea(Idea *i) { repo.addIdea(i); }
		void addResearcher(std::string name, std::string position) { 
			Researcher *r = new Researcher(name, position); repo.addResearcher(r); }
		void addIdea(std::string title, std::string description, std::string status, std::string creator, int duration) { 
			Idea *i = new Idea(title, description, status, creator, duration); repo.addIdea(i); }
		std::vector<Researcher*> getResearchers() { return repo.getResearchers(); }
		std::vector<Idea*> getIdeas() { return repo.getIdeas(); }
		void saveAllAccepted() { repo.saveAccepted(); }
		~Service() {}
};

