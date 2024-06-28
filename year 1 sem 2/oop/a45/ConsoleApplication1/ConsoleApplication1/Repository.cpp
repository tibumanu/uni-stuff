#include "repository.h"
//#include "../../../../../msys64/mingw64/include/c++/12.2.0/bits/algorithmfwd.h"

Repository::Repository() {
    initialize();
}

Repository::~Repository() {
    saveToFile("repooo.txt");
}

bool Repository::saveToFile(std::string filename){
    if(filename.empty())    return false;
    std::ofstream fout(filename);
    for(const auto& i : this->data) fout << i << '\n';
}

bool Repository::loadFromFile(std::string filename) {
    if (filename.empty())    return false;
    std::ifstream fin(filename);
    if (!fin.is_open()) return false;
    Movie loadedMovie;
    while(fin >> loadedMovie)
        if(this->findMovie(loadedMovie.getName(), loadedMovie.getYear()) == -1)
			this->addMovie(loadedMovie);
    fin.close();
	return true;
}

bool Repository::initialize(){
    return loadFromFile("repooo.txt");
}

int Repository::getSize() const {
    return data.size();
}

Movie Repository::getMovie(int index) const {
    // returns the Element found at position `index` within the repo
    return data[index];
}


// experimental atm
Movie* Repository::getMoviePtr(int index){
    return &data[index];
}



int Repository::findMovie(const std::string& givenName, int givenYear) {
    // /// OLD CODE COMMENTED
    // returns the index of the Element which has `givenName` as name, and `givenYear` as year.
    // returns -1 if no such Element exists
    // for (int i = 0; i < this->getSize(); i++)
    //     if ((this->getMovie(i).getName() == givenName) && (this->getMovie(i).getYear() == givenYear))
    //         return i;
    // return -1;
    // using STL algorithms
    auto it = std::find_if(data.begin(), data.end(), [givenName, givenYear](Movie movie) { 
        return (movie.getName() == givenName && movie.getYear() == givenYear); });
    if (it == data.end() || data.empty())
        return -1;
    return std::distance(data.begin(), it);

}

int Repository::addMovie(Movie givenMovie) {
    // adds a the Movie `givenMovie` to the repo.
    // if it already exists within the repo, returns -1. returns 1 otherwise.
    if (data.empty())    data.push_back(givenMovie);
    if (this->findMovie(givenMovie.getName(), givenMovie.getYear()) == -1) {
        data.push_back(givenMovie);
        return 1;
    }
    else
        return -1;
}

int Repository::removeMovie(std::string givenName, int givenYear) {
    // removes the Movie with the name `givenName` and the year `givenYear`.
    // returns 0 if no such Movie exists, 1 otherwise.
    int index = findMovie(givenName, givenYear);
    if (index == -1) return 0;
    data.erase(data.begin() + index);
    return 1;
}

