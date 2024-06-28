#include <iostream>
#include "ui.h"
#include <crtdbg.h>
#include "tests.h"

int main() {
    
    /*testDynamicArr();
    testDomain();
    testRepo();
    testService();*/

    UI* ui = new UI();
    ui->startGeneral();
    delete ui;

    std::cout << "LEAKs: " << _CrtDumpMemoryLeaks();
    return 0;
}
