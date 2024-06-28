#pragma once
#include "Repository.h"
class Service
{
private:
	Repository& repo;

public:
	Service(Repository& repo);
	~Service();

	void addDocument(std::string name, std::string keywords, std::string content);
	void removeDocument(std::string name);
	std::vector<Document> getDocuments();
	std::vector<Document> searchForTextInDocuments(std::string text);
	Document getDocumentByName(std::string name);
};

