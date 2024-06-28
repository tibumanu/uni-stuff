#include "../repository/repository.h"
#include "../service/service.h"
#include <stdio.h>

typedef struct{
    Service *service;
}UI;

void printMenu();
void start();
UI* createUI(Service *service);
