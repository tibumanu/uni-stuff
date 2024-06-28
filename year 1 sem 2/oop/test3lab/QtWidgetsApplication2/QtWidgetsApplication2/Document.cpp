#include "Document.h"

Document::Document() = default;

Document::Document(std::string name, std::string keywords, std::string content)
{
	this->name = name;
	this->keywords = keywords;
	this->content = content;
}

Document::~Document() = default;


std::string Document::getName()
{
	return name;
}

std::string Document::getKeywords()
{
	return keywords;
}

std::string Document::getContent()
{
	return content;
}

void Document::setName(std::string name)
{
	this->name = name;
}

void Document::setKeywords(std::string keywords)
{
	this->keywords = keywords;
}

void Document::setContent(std::string content)
{
	this->content = content;
}

std::string Document::toString()
{
	return name + "|" + keywords + "|" + content;
}

bool Document::operator==(const Document& other) const
{
	return name == other.name;
}
