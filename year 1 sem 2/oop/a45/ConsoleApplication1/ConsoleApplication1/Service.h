#pragma once
#include "repository.h"

class Service {
private:
    Repository* repo;

public:
    Service();
    ~Service();

    Repository* getRepo();

    int updateName(const std::string& givenName, int givenYear, const std::string& newName);
    int updateYear(const std::string& givenName, int givenYear, int newYear);
    int updateGenre(const std::string& givenName, int givenYear, const std::string& newGenre);
    int updateLikes(const std::string& givenName, int givenYear, int newLikes);
    int updateLink(const std::string& givenName, int givenYear, const std::string& newLink);

    int addMovieService(const Movie&);
    int deleteMovieService(const Movie&);

private:
    void add10Items();

};

