#include <stdio.h>
#include <time.h>
#include <crtdbg.h>
#include <string.h>
#include <stdlib.h>
#include "domain/domain.h"
#include "dynamicArray/dynamicArray.h"
#include "repository/repository.h"



int main()
{
    // printf("Hello, World!\n");
    // Country test;
    // test = createCountry("Romania", "Europe", 20000000);
    // Country test2;
    // test2 = createCountry("XYZ", "ABC", 10000);
    //  char str[100];
    //  toString(&test, str);
    //  printf("%s\n", str);
    DynamicArray arr = createDynamicArray(10);
    Repository repo = createRepository();
    printRepo(&repo);
    
    
    return 0;
}