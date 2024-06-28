#include "service.h"

int filterCountries(Repository *repo, const char filterString[], Country validCountries[]) {
    // filters the countries from the repository
    // input: repo - pointer to repository, filterString - string, validCountries - array of Countrys which will be filled with the filtered countries
    // output: integer - number of filtered countries
    int counter = 0;
    int index;
    if(filterString[0] == '\0') // case for when the string is empty
        for (index = 0; index < repo->arr.index; index++) {
            strcpy(validCountries[counter].name, repo->arr.data[index].name);
            strcpy(validCountries[counter].continent, repo->arr.data[index].continent);
            validCountries[counter].population = repo->arr.data[index].population; // copy everything in the array[counter]
            counter++; // increase the number of elements from the array
        }
    else {
        for (index = 0; index < repo->arr.index; index++) {
            if (strstr(repo->arr.data[index].name, filterString) != NULL) { // if the string can be found in the name, copy in array[counter]
                strcpy(validCountries[counter].name, repo->arr.data[index].name);
                strcpy(validCountries[counter].continent, repo->arr.data[index].continent);
                validCountries[counter].population = repo->arr.data[index].population;
                counter++; // increase the number of elements from the array
            }
        }
    }
    return counter;
}
