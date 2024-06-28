#pragma once
#include <vector>
#include "Document.h"
class Repository
{
private:
	std::vector<Document> documents;

public:
	Repository();
	~Repository();

	void addDocument(Document document);
	void addDocumentByFields(std::string name, std::string keywords, std::string content);
	void removeDocument(Document document);
	std::vector<Document> getDocuments();

	void readFromFile(std::string fileName);
};

