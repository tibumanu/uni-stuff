#include "Scanner.h"
#include <unistd.h>
#include <direct.h>
#include <iostream>

int main() {
    // change the current working directory to the one where the programs are located
    // else, default directory will be C:\msys64\mingw64\bin
    const char* directory = "C:\\uni\\3\\FLCD\\lab3";
    if (_chdir(directory) != 0) {
        std::cerr << "Error changing directory to " << directory << std::endl;
        return -1;
    }

    Scanner scanner = Scanner();

    char buf[255];
    getcwd(buf, sizeof(buf));
    std::printf("Current working directory: %s\n", buf);

    std::string filename = "";
    std::cout << "Enter the name of the file you want to scan: ";
    std::cin >> filename;
    scanner.lexicalAnalysis(filename);

    return 0;
}
