#pragma once
#include <string>

class Document
{

private:
	std::string name;
	std::string keywords;
	std::string content;

public:
	Document();
	Document(std::string name, std::string keywords, std::string content);
	~Document();

	std::string getName();
	std::string getKeywords();
	std::string getContent();

	void setName(std::string name);
	void setKeywords(std::string keywords);
	void setContent(std::string content);

	std::string toString();
	bool operator==(const Document& other) const;
};

