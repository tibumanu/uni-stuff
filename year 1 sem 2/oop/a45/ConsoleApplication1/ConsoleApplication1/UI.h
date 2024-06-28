#pragma once
#include <iostream>

#include "service.h"



class UI {
private:
    Service* service;
    DynamicArray<Movie> watchlist;

public:
    UI();
    ~UI();

    void startGeneral();

private:
    void startAdmin();
    void startClient();
    static void printMenuClient();
    static void printMenu();
    void printAll();
    void addMovieUI();
    void deleteMovieUI();
    void updateMovieUI();
    void seeMovies(const std::string& givenGenre);
    void deleteAndRate();
    void seeWatchlist();
};

