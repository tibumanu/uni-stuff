#pragma once

typedef struct {
    char name[50];
    char continent[50];
    unsigned long int population;
} Country;

Country createCountry(char name[], char continent[], unsigned long int population);
char* getName(Country* country);
char* getContinent(Country* country);
unsigned long int getPopulation(Country* country);
void toString(Country* country, char str[]);
