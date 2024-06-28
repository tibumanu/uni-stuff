#include "domain.h"

#include <utility>
#include <sstream>
#include <vector>

Movie::Movie() {
    this->year = 0;
    this->link = "";
    this->genre = "";
    this->name = "";
}

Movie::~Movie() = default;

Movie::Movie(const std::string& name, const int& year, const std::string& genre, const int& likes,
    const std::string& link) {
    this->name = name;
    this->year = year;
    this->genre = genre;
    this->likes = likes;
    this->link = link;
}

Movie::Movie(const Movie& copy) {
    this->name = copy.name;
    this->year = copy.year;
    this->genre = copy.genre;
    this->likes = copy.likes;
    this->link = copy.link;
}

std::string Movie::getName() const {
    return this->name;
}

int Movie::getYear() const {
    return this->year;
}

std::string Movie::getGenre() const {
    return this->genre;
}

int Movie::getLikes() const {
    return this->likes;
}

std::string Movie::getLink() const {
    return this->link;
}

void Movie::setName(std::string newName) {
    this->name = std::move(newName);
}

void Movie::setYear(int newYear) {
    this->year = newYear;
}

void Movie::setGenre(std::string newGenre) {
    this->genre = std::move(newGenre);
}

void Movie::setLikes(int newLikes) {
    this->likes = newLikes;
}

void Movie::setLink(std::string newLink) {
    this->link = std::move(newLink);
}

std::string Movie::toString() const {
    // returns a string containing info about the Movie.
    // the format is the following:
    // NAME: <name>, YEAR: <year>, GENRE: <genre>, LIKES: <no. of likes>, LINK: <link>
    std::string str = "";
    str += "NAME: ";
    str += this->name;
    str += ", YEAR: ";
    str += std::to_string(this->year);
    str += ", GENRE: ";
    str += this->genre;
    str += ", LIKES: ";
    str += std::to_string(this->likes);
    str += ", LINK: ";
    str += this->link;
    str += "\n";

    return str;
}


bool Movie::operator==(const Movie& m) {
    return (this->name == m.name && this->year == m.year);
}


static std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::ostream& operator<<(std::ostream& out, const Movie& movie)
{
    // TODO: insert return statement here
    // prints the given movie to the output stream; used for saving to file; info is saved on one single line
    out << movie.getName() << ", " << movie.getYear() << ", " << movie.getGenre() << ", " << movie.getLikes() << ", " << movie.getLink();
    return out;
}

std::istream& operator>>(std::istream& input, Movie& movie) {
    std::string line;
    std::getline(input, line);
    std::vector<std::string> tokens;

    if (line.empty())    return input;
    tokens = tokenize(line, ',');
    movie.name = tokens[0];
    movie.year = std::stoi(tokens[1]);
    movie.genre = tokens[2];
    movie.likes = std::stoi(tokens[3]);
    movie.link = tokens[4];

    return input;
}
