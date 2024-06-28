#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../dynamicArray/dynamicArray.h"

typedef struct{
    DynamicArray arr;
}Repository;


Repository createRepository();
void addCountry(Repository *repo, Country country);
 int findByNameContains(Repository *repo, char name[]);
 int findByNameExact(Repository *repo, char name[]);
void deleteCountry(Repository *repo, char name[]);
void updateCountry(Repository *repo, int oldPos, Country newCountry);
void migrationUpdate(Repository *repo, int fromWherePos, int toWherePos, unsigned long int migrators);
void populateRepo(Repository *repo);
void printRepo(Repository *repo);
