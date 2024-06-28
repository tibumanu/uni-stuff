#include <stdbool.h>
#include "../repository/repository.h"

bool checkValidnessContinent(char continent[]);
int addCountry(Repository *repo, char name[], char continent[], unsigned long int population);
bool deleteCountry(Repository *repo, char name[]);
int updateCountry(Repository *repo, char old_name[], char name[], char continent[], unsigned long int newPop);
int filterCountry(Repository *repo, const char filterString[], Country validCountry[]);
int migration(Repository *repo, char fromCountryName[], char toCountryName[], unsigned long int howMany);
int filterAfterContinent(Repository *repo, Country validCountries[], char continentInput[], unsigned long int population);
int ServiceUndo(Repository *repo);
int ServiceRedo(Repository *repo);