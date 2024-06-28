#include <stdio.h>
#include <string.h>
#include "domain.h"

Country createCountry(char name[], char continent[], unsigned long int population) {
    // creates country
    // input: name, continent, population
    // output: country
    Country c;
    strcpy(c.name, name);
    strcpy(c.continent, continent);
    c.population = population;
    return c;
}

char* getName(Country* c) {
    // returns the name of a country
    // input: country
    // output: name
    return c->name;
}

char* getContinent(Country* c) {
    // returns the continent of a country
    // input: country
    // output: continent
    return c->continent;
}

unsigned long int getPopulation(Country* c) {
    // returns the population of a country
    // input: country
    // output: population
    return c->population;
}

void toString(Country* c, char str[]) {
    // returns the string representation of a country
    // input: country
    // output: string
    sprintf(str, "Country: %s, continent: %s, pop: %lu", c->name, c->continent, c->population);
}