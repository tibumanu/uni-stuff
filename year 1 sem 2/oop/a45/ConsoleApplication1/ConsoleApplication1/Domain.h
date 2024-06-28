#pragma once
#include <string>
#include <iostream>


class Movie {
private:
    std::string genre = "";
    std::string name = "";
    int year = 0;
    int likes = 0;
    std::string link = "";

public:
    Movie();
    ~Movie();
    Movie(const std::string& name, const int& year, const std::string& genre, const int& likes, const std::string& link);
    Movie(const Movie&);

    std::string getName()const;
    int getYear()const;
    std::string getGenre()const;
    int getLikes()const;
    std::string getLink()const;

    void setName(std::string name);
    void setYear(int year);
    void setGenre(std::string genre);
    void setLikes(int likes);
    void setLink(std::string link);
    bool operator==(const Movie& s);
    friend std::ostream& operator<<(std::ostream& out, const Movie& s);
    friend std::istream& operator>>(std::istream& in, Movie& s);

    std::string toString()const;
    //^to return string

};

