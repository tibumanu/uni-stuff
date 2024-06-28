#pragma once
#include "DynamicArray.h"
#include <iostream>
#include <vector>
#include <fstream>


class Repository {
private:
    std::vector<Movie> data;

public:
    Repository();
    ~Repository();

    bool saveToFile(std::string filename);
    bool loadFromFile(std::string filename);

    bool initialize();

    int getSize()const;
    Movie getMovie(int index)const;
    Movie* getMoviePtr(int index);

    int findMovie(const std::string& givenName, int givenYear);
    int addMovie(Movie givenMovie);
    int removeMovie(std::string givenName, int givenYear);
};

