#include "Repository.h"
#include <fstream>
#include <sstream>

Repository::Repository()
{
	this->readFromFile("data.txt");
}

Repository::~Repository() = default;


void Repository::addDocument(Document document)
{
	// check for unique name
	for (auto& doc : documents)
		if (doc.getName() == document.getName())
			throw std::exception("Document's name should be unique.");
	documents.push_back(document);
}

void Repository::addDocumentByFields(std::string name, std::string keywords, std::string content)
{
	Document* document = new Document(name, keywords, content);
	documents.push_back(*document);
}

void Repository::removeDocument(Document document)
{
	documents.erase(std::remove(documents.begin(), documents.end(), document), documents.end());
}

std::vector<Document> Repository::getDocuments()
{
	return documents;
}

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

void Repository::readFromFile(std::string fileName)
{

	std::ifstream fin(fileName);
	if (!fin.is_open())
		throw std::exception("File could not be opened.");
	std::string line;
	while (std::getline(fin, line))
	{
		std::vector<std::string> tokens = tokenize(line, '|');
		if (tokens.size() != 3)
			continue;
		Document document(tokens[0], tokens[1], tokens[2]);
		this->addDocument(document);
	}
	fin.close();
}






