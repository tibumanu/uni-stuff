#include "Service.h"

Service::Service(Repository& repo) : repo(repo) {
	;
}

Service::~Service() = default;

void Service::addDocument(std::string name, std::string keywords, std::string content){
	repo.addDocumentByFields(name, keywords, content);
}

void Service::removeDocument(std::string name) {
	Document doc = Document(name, "", "");
	repo.removeDocument(doc);
}

std::vector<Document> Service::getDocuments()
{
	return this->repo.getDocuments();
}

std::vector<Document> Service::searchForTextInDocuments(std::string text)
{
	std::vector<Document> documents = this->repo.getDocuments();
	std::vector<Document> result;
	for (Document doc : documents) {
		if (doc.getName().find(text) != std::string::npos || doc.getKeywords().find(text) != std::string::npos) {
			result.push_back(doc);
		}
	}
	return result;
}

Document Service::getDocumentByName(std::string name){ 
	std::vector<Document> documents = this->repo.getDocuments();
	Document bestMatch = Document("", "", "");
	float bestMatchScore = 0;
	for (Document doc : documents) {
		// if the name isn't a substring of the document's name, the score is 0; we skip the rest
		if(doc.getName().find(name) == std::string::npos)
			continue;
		float score = 0;
		for (int i = 0; i < name.size(); i++) {
			if (doc.getName().find(name[i]) != std::string::npos) {
				score += 1;
			}
		}
		score = score / doc.getName().size();
		if (score > bestMatchScore) {
			bestMatch = doc;
			bestMatchScore = score;
		}
	}
	return bestMatch;
}
