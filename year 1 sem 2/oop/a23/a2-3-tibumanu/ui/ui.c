#include "ui.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void printMenu() {
    printf("a. populate repo\n");
    printf("b. print repo\n");
    printf("c. add a country\n");
    printf("d. delete a country\n");
    printf("e. migrate\n");
    printf("f. exit\n");
}


void start(){
    char choice;

    while(1) {
        printMenu();
        printf("\n>    ");
        scanf_s(" %c", &choice, sizeof(choice));
        if (choice == 'a') {
            populateRepo(&repo);
        } else if (choice == 'b') {
            printRepo(&repo);
            
        } else if (choice == 'c') {
            char name[50];
            char continent[50];
            char population_string[50];
            unsigned long int population;
            printf("Enter the name of the country, name of the continent and population: \n");
            scanf_s(" %[^\n]", &name, sizeof(name));
            scanf_s("%s", &continent, sizeof(continent));
            scanf_s("%s", &population_string, sizeof(population_string));
            population = strtol(population_string, NULL, 10);
            addCountry(&repo, createCountry(name, continent, population));
        } else if (choice == 'd') {
            char name[50];
            char continent[50];
            char population_string[50];
            unsigned long int population;
            printf("Enter the name of the country: \n");
            scanf_s(" %[^\n]", &name, sizeof(name));
            deleteCountry(&repo, (char*)&name);
            } else if (choice == 'e') {
            printf("Enter the start end of the migration: \n");
            char name1[50];
            scanf_s(" %[^\n]", &name1, sizeof(name1));
            printf("Enter the end of the migration: \n");
            char name2[50];
            scanf_s(" %[^\n]", &name2, sizeof(name2));
            unsigned long int population;
            printf("Enter the number of people migrating: \n");
            scanf_s("%lu", &population);
            migrationUpdate(&repo, findByNameExact(&repo, name1), findByNameExact(&repo, name2), population);
        } else if (choice == 'f') {
            return 0;
        }else printf("\nwrong input. try again\n");
    }
}

void option_2(Repository *country_list) {
    char name[50];
    char continent[50];
    char population_string[50];
    unsigned long int population;
    printf("Enter the name of the country, name of the continent and population: \n");
    scanf_s(" %[^\n]", &name, sizeof(name));
    scanf_s("%s", &continent, sizeof(continent));
    scanf_s("%s", &population_string, sizeof(population_string));
    population = strtol(population_string, NULL, 10);
    int added = add_country(country_list, name, continent, population);
    if (added == 1)
        printf("Country %s already exists in the list.\n", name);
    else if (added == 2)
        printf("The continent %s is not a valid one.\n", continent);
    else
        printf("Country %s successfully added.\n", name);
}
