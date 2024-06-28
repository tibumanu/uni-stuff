#define NOMINMAX
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <cstring>
#include <iostream>
#include <codecvt>
#include <fstream>
#include <limits>
#include "ui.h"
using namespace std;

UI::UI() {
    service = new Service();
}

UI::~UI() {
    delete service;
}

void UI::printMenu() {
    std::cout << "\tMOVIE DATABASE MENU\n";
    std::cout << "1. Add movie\n";
    std::cout << "2. Delete movie\n";
    std::cout << "3. Update movie\n";
    std::cout << "4. Show all movies\n";
    std::cout << "0. Exit\n";
}

void UI::printMenuClient() {
    std::cout << "\tCLIENT MENU\n";
    std::cout << "1. See movies from database with given genre.\n";
    std::cout << "2. Remove (& rate) movie from watchlist.\n";
    std::cout << "3. See watchlist\n";
    std::cout << "0. Exit\n";
};

void UI::startAdmin() {
    while (true) {
        printMenu();
        int command;
        std::cin >> command;
        switch (command) {
        case 0:
            return;
        case 1: {
            addMovieUI();
            break;
        }
        case 2: {
            deleteMovieUI();
            break;
        }
        case 3: {
            updateMovieUI();
            break;
        }
        case 4: {
            printAll();
            break;
        }
        default: {
            std::cout << "\nInvalid input, try again...\n";
            break;
        }
        }
    }
}

void UI::startGeneral() {
    std::string user, pwd;
    std::cout << "\nuser:\t>";
    std::cin >> user;
    std::cout << "\npassword:\t>";
    std::cin >> pwd;

    if (user == "client" && pwd == "qwerty")
        startClient();
    else
        if (user == "admin" && pwd == "admin")
            startAdmin();
}

void UI::startClient() {
    while (true) {
        printMenuClient();
        int command;
        std::cin >> command;
        switch (command) {
        case 1: {
            std::string givenGenre;
            // clear buffer
            std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, givenGenre);
            if (givenGenre.length() == 0)
                givenGenre = "";
            seeMovies(givenGenre);
            break;
        }
        case 2: {
            deleteAndRate();
            break;
        }
        case 3: {
            seeWatchlist();
            break;
        };
        case 0: {
            return;
        }
        default: {
            std::cout << "\nInvalid input, try again...\n";
            break;
        }
        }
    }
}

void UI::printAll() {
    // prints all the Movies from within the repo.
    int size = service->getRepo()->getSize();
    for (int i = 0; i < size; i++) {
        Movie movie = service->getRepo()->getMovie(i);
        std::cout << movie.toString() << "\n";
    }
    std::cout << "### END OF LIST.\n";
}

void UI::addMovieUI() {
    // clear input buffer
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    std::string name = "";
    int year;
    std::string genre = "";
    int likes;
    std::string link = "";

    std::cout << "\nMovie name:   >";
    std::getline(std::cin, name);

    std::cout << "\nYear:     >";
    std::cin >> year;
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nGenre:    >";
    std::getline(std::cin, genre);

    std::cout << "\nLikes:    >";
    std::cin >> likes;
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nLink:     >";
    std::getline(std::cin, link);


    Movie movie = Movie(name, year, genre, likes, link);
    if (service->addMovieService(movie) != -1) {
        std::cout<<movie.toString();
        std::cout << "\nSuccessfully added movie.\n";
        return;
    }
    else
        std::cout << "\nCouldn't add movie - probably already in the database.\n";
}

void UI::deleteMovieUI() {
    std::string name;
    int year;

    std::cout << "\nName of the movie:      >";
    while (name.length() == 0)  //since the buffer screws me over
        std::getline(std::cin, name);

    std::cout << "\nYear of the movie:    >";
    std::cin >> year;

    int index = service->getRepo()->findMovie(name, year);
    if (index == -1) {
        std::cout << "No such movie in database.\n\n";
        return;
    }
    Movie movie = service->getRepo()->getMovie(index);

    if (service->deleteMovieService(movie))
        std::cout << "\nSuccessfully removed movie.\n\n";
    else
        std::cout << "\nCouldn't delete given movie.\n\n";

}

void UI::updateMovieUI() {
    std::string givenName;
    int givenYear;

    std::cout << "\nName of the movie:      >";
    while (givenName.length() == 0)  //since the buffer screws me over
        std::getline(std::cin, givenName);

    std::cout << "\nYear of the movie:    >";
    std::cin >> givenYear;

    int index = service->getRepo()->findMovie(givenName, givenYear);
    if (index == -1) {
        std::cout << "No such movie found in database.\n\n";
        return;
    }

    //Movie movie = service->getRepo()->getMovie(index);



    while (true) {
        std::cout << "\nWhat would you like to update?\n";
        std::cout << "1. Name\n2. Year\n3. Genre\n4. Likes\n5. Link\n0. Nevermind, get me out.\n";
        int what;
        std::cin >> what;
        switch (what) {
        case 0: {
            return;
        }
        case 1: {
            std::string newName;
            std::cout << "\nNew name:     >";
            while (newName.length() == 0)
                std::getline(std::cin, newName);
            if (service->updateName(givenName, givenYear, newName))
                std::cout << "\nSuccessfully updated movie.\n";
            else
                std::cout << "\nCouldn't update movie.\n";
            return;
        }
        case 2: {
            int newYear;
            std::cout << "\nNew year:     >";
            std::cin >> newYear;
            if (service->updateYear(givenName, givenYear, newYear))
                std::cout << "\nSuccessfully updated movie.\n";
            else
                std::cout << "\nCouldn't update movie.\n";
            return;
        }
        case 3: {
            std::string newGenre;
            std::cout << "\nNew genre:     >";
            while (newGenre.length() == 0)
                std::getline(std::cin, newGenre);
            if (service->updateGenre(givenName, givenYear, newGenre))
                std::cout << "\nSuccessfully updated movie.\n";
            else
                std::cout << "\nCouldn't update movie.\n";
            return;
        }
        case 4: {
            int newLikes;
            std::cout << "\nNew no. of likes:     >";
            std::cin >> newLikes;
            if (service->updateLikes(givenName, givenYear, newLikes))
                std::cout << "\nSuccessfully updated movie.\n";
            else
                std::cout << "\nCouldn't update movie.\n";
            return;
        }
        case 5: {
            std::string newLink;
            std::cout << "\nNew link:     >";
            std::cin >> newLink;
            if (service->updateLink(givenName, givenYear, newLink))
                std::cout << "\nSuccessfully updated movie.\n";
            else
                std::cout << "\nCouldn't update movie.\n";
            return;
        }
        default: {
            std::cout << "\nInvalid input, try again\n";
            break;
        }
        }

    }
}


void UI::seeMovies(const std::string& givenGenre) {
    int stop = 0, index = 0;
    while (!stop) {
        Movie m = service->getRepo()->getMovie(index % service->getRepo()->getSize());
        if (m.getGenre().find(givenGenre) != std::string::npos) {
            std::cout << m.toString();
            std::string link = m.getLink();

            // Convert link to wide character string
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wideLink = converter.from_bytes(link);

            //ShellExecute(NULL, 0, wideLink.c_str(), NULL, NULL, SW_SHOWNORMAL);
            std::cout << "\n\tWassup?\n";
            std::cout << "1. Liked it\n2. Disliked it.\n0. Get me out\n\t>";
            int liked = -1;
            std::cin >> liked;
            if (liked == 1) {
                std::string choice;
                std::cout << "\nAdd it to watchlist? (Y/N)";
                std::cin >> choice;
                if (choice == "Y")
                    watchlist.addItem(m);
                else;
            }
            if (liked == 0)
                stop = 1;
        }
        index++;
    }
}



void UI::deleteAndRate() {
    std::string givenName;
    int givenYear;

    std::cout << "\nName of the movie:      >";
    while (givenName.length() == 0)  //since the buffer screws me over
        std::getline(std::cin, givenName);

    std::cout << "\nYear of the movie:    >";
    std::cin >> givenYear;

    int index = service->getRepo()->findMovie(givenName, givenYear);
    if (index == -1) {
        std::cout << "No such movie found in database.\n\n";
        return;
    }
    Movie* m = service->getRepo()->getMoviePtr(index);
    std::string choice;
    std::cout << m->toString();
    std::cout << "\nLiked this movie? (Y/N)\n\t>";
    std::cin >> choice;
    if (choice == "Y")
        m->setLikes(m->getLikes() + 1);
    int indexWatchlist = watchlist.findItem(*m);
    watchlist.removeItem(indexWatchlist);
}

void UI::seeWatchlist() {
    for (int i = 0; i < watchlist.getSize(); i++)
        std::cout << watchlist.getItem(i).toString();
}
