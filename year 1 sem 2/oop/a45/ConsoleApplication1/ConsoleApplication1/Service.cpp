#include "service.h"

#include <utility>

Service::Service() {
    repo = new Repository();
    //add10Items();
}

Service::~Service() {
    delete repo;
}

Repository* Service::getRepo() {
    return repo;
}

int Service::updateName(const std::string& givenName, int givenYear, const std::string& newName) {
    // updates the Name of the Movie with the name `givenName` and the year `givenYear`
    // returns 0 if no such movie exists.
    // returns 1 on success.
    int index = repo->findMovie(givenName, givenYear);
    if (index == -1) return 0;

    Movie movie = repo->getMovie(index);
    movie.setName(newName);
    repo->removeMovie(givenName, givenYear);
    repo->addMovie(movie);

    return 1;
}

int Service::updateYear(const std::string& givenName, int givenYear, int newYear) {
    int index = repo->findMovie(givenName, givenYear);
    if (index == -1) return 0;

    Movie movie = repo->getMovie(index);
    movie.setYear(newYear);
    repo->removeMovie(givenName, givenYear);
    repo->addMovie(movie);

    return 1;
}

int Service::updateGenre(const std::string& givenName, int givenYear, const std::string& newGenre) {
    int index = repo->findMovie(givenName, givenYear);
    if (index == -1) return 0;

    Movie movie = repo->getMovie(index);
    movie.setGenre(newGenre);
    repo->removeMovie(givenName, givenYear);
    repo->addMovie(movie);

    return 1;
}

int Service::updateLikes(const std::string& givenName, int givenYear, int newLikes) {
    int index = repo->findMovie(givenName, givenYear);
    if (index == -1) return 0;

    Movie movie = repo->getMovie(index);
    Movie* moviePtr = repo->getMoviePtr(index);
    moviePtr->setLikes(newLikes);
    /*movie.setLikes(newLikes);
    repo->removeMovie(givenName, givenYear);
    repo->addMovie(movie);*/

    return 1;
}

int Service::updateLink(const std::string& givenName, int givenYear, const std::string& newLink) {
    int index = repo->findMovie(givenName, givenYear);
    if (index == -1) return 0;

    Movie movie = repo->getMovie(index);
    movie.setLink(newLink);
    repo->removeMovie(givenName, givenYear);
    repo->addMovie(movie);

    return 1;
}

int Service::addMovieService(const Movie& givenMovie) {
    return repo->addMovie(givenMovie);
}

int Service::deleteMovieService(const Movie& givenMovie) {
    return repo->removeMovie(givenMovie.getName(), givenMovie.getYear());
}

void Service::add10Items() {
    Movie m1 = Movie("Blade Runner 2049", 2017, "Action/Drama", 500000, "https://www.imdb.com/title/tt1856101");
    Movie m2 = Movie("Nightcrawler", 2014, "Crime/Drama", 375000, "https://www.imdb.com/title/tt2872718");
    Movie m3 = Movie("No Country for Old Men", 2007, "Crime/Thriller", 700000, "https://www.imdb.com/title/tt1856101");
    Movie m4 = Movie("Taxi Driver", 1976, "Crime/Drama", 575000, "https://www.imdb.com/title/tt0075314");
    Movie m5 = Movie("Forrest Gump", 1994, "Drama/Romance", 650000, "https://www.imdb.com/title/tt0075314");
    Movie m6 = Movie("The Silence of the Lambs", 1991, "Crime/Thriller", 300000, "https://www.imdb.com/title/tt0102926");
    Movie m7 = Movie("Good Will Hunting", 1997, "Drama/Romance", 475000, "https://www.imdb.com/title/tt0119217");
    Movie m8 = Movie("All Quiet on the Western Front", 2022, "Action/Drama", 650000, "https://www.imdb.com/title/tt1016150");
    Movie m9 = Movie("The Pianist", 2002, "Biography/Drama", 500000, "https://www.imdb.com/title/tt0253474");
    Movie m10 = Movie("The Iron Giant", 1999, "Animation/Adventure", 425000, "https://www.imdb.com/title/tt0129167");

    this->addMovieService(m1);
    this->addMovieService(m2);
    this->addMovieService(m3);
    this->addMovieService(m4);
    this->addMovieService(m5);
    this->addMovieService(m6);
    this->addMovieService(m7);
    this->addMovieService(m8);
    this->addMovieService(m9);
    this->addMovieService(m10);

}


