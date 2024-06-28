#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repository.h"
#include "../dynamicArray/dynamicArray.h"

int findByNameContains(Repository *repo, char name[]);
int findByNameExact(Repository *repo, char name[]);

Repository createRepository(){
    // creates repository
    // input: none
    // output: repository
    Repository repo;
    DynamicArray arr = createDynamicArray(10);
    repo.arr = arr;
    return repo;
}

void addCountry(Repository* repo, Country country) {
    // adds country to repository
    // input: repo - pointer to repository, country - Country
    // output: none
    addElement(&repo->arr, country);
}

int findByNameContains(Repository* repo, char* name) {
    // finds country in repository
    // input: repo - pointer to repository, name - string
    // output: integer - position of country in repository    
    

    for (int i = 0; i < getArrayLength(&repo->arr); i++) {
        if (strstr(getElements(&repo->arr)[i].name, name) != NULL)
            return i;
    }
    return -1;
}

int findByNameExact(Repository* repo, char* name) {
    // finds country in repository
    // input: repo - pointer to repository, name - string
    // output: integer - position of country in repository
    for (int i = 0; i < getArrayLength(&repo->arr); i++) {
        if (strcmp(getElements(&repo->arr)[i].name, name) == 0)
            return i;
    }
    return -1;
}

void deleteCountry(Repository* repo, char name[]) {
    // deletes country from repository
    // input: repo - pointer to repository, name - string
    // output: none
    int pos = findByNameExact(repo, name);
    if (pos == -1)
        return;
    deleteElement(&repo->arr, pos);
}

void updateCountry(Repository* repo, int pos, Country country) {
    // updates country from repository
    // input: repo - pointer to repository, pos - integer, country - Country
    // output: none
    updateElement(&repo->arr, pos, country);
}

void migrationUpdate(Repository* repo, int fromPos, int toPos, unsigned long int howMany){
    // updates migration from one country to another
    // input: repo - pointer to repository, fromPos - integer which is position from where people migrate, 
    //  toPos - integer which is position to where people migrate, howMany - integer
    // output: none
    repo->arr.data[fromPos].population -= howMany;
    repo->arr.data[toPos].population += howMany;
}

void populateRepo(Repository* repo){
    // populates repository with some countries
    // input: repo - pointer to repository
    // output: none
    Country c1 = createCountry("Romania", "Europe", 20000000);
    Country c2 = createCountry("USA", "America", 300000000);
    Country c3 = createCountry("China", "Asia", 1000000000);
    Country c4 = createCountry("Russia", "Europe", 150000000);
    Country c5 = createCountry("Brazil", "America", 200000000);
    Country c6 = createCountry("India", "Asia", 1000000000);
    addCountry(repo, c1);
    addCountry(repo, c2);
    addCountry(repo, c3);
    addCountry(repo, c4);
    addCountry(repo, c5);
    addCountry(repo, c6);
}

void printRepo(Repository* repo){
    // prints repository
    // input: repo - pointer to repository
    // output: none
    for (int i = 0; i < getArrayLength(&repo->arr); i++){
        char str[100];
        toString(&repo->arr.data[i], str);
        printf("%s\n", str);
    }
}