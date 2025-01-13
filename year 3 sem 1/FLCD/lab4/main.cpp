#include "Scanner.h"
#include "FA.h"
#include <unistd.h>
#include <direct.h>
#include <iostream>

int main() {
    // change the current working directory to the one where the programs are located
    // else, default directory will be C:\msys64\mingw64\bin
    const char* directory = "C:\\uni\\3\\FLCD\\lab4";
    if (_chdir(directory) != 0) {
        std::cerr << "Error changing directory to " << directory << std::endl;
        return -1;
    }


    char buf[255];
    getcwd(buf, sizeof(buf));
    std::printf("Current working directory: %s\n", buf);
    
    //Scanner scanner = Scanner();

    // std::string filename = "";
    // std::cout << "Enter the name of the file you want to scan: ";
    // std::cin >> filename;
    // scanner.lexicalAnalysis(filename);

    // FA fa1 = FA("FA1.in");
    // std::cout << "FA1: " << fa1.isDeterministic() << std::endl;

    // FA fa2 = FA("FA2.in");
    // std::cout << "FA2: " << fa2.isDeterministic() << std::endl;

    // fa1.print();

    // a menu: 1. user enters FA filename; 2. print FA; 3. check if FA is deterministic; 4. check if a sequence is accepted by the FA; 5. exit
    std::string faFilename;
    std::string programFilename;
    int option;
    Scanner scanner = Scanner();
    FA fa = FA();   
    while (true) {
        std::cout << "1. Enter FA filename" << std::endl;
        std::cout << "2. Print FA" << std::endl;
        std::cout << "3. Check if FA is deterministic" << std::endl;
        std::cout << "4. Check if a sequence is accepted by the FA" << std::endl;
        std::cout << "5. Check if input program is lexically correct" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cin >> option;
        std::string sequence;
        switch (option) {
            case 1:
                std::cout << "Enter FA filename: ";
                std::cin >> faFilename;
                fa.loadFromFile(faFilename);
                break;
            case 2:
                fa.print();
                break;
            case 3:
                std::cout << "FA is deterministic: " << fa.isDeterministic() << std::endl;
                break;
            case 4:
                std::cout << "Enter sequence: ";
                std::cin >> sequence;
                std::cout << "Sequence is accepted: " << fa.isAccepted(sequence) << std::endl;
                break;
            case 5:
                std::cout << "Enter the name of the file you want to scan: (if no output is displayed, the program is lexically correct)" << std::endl;
                std::cin >> programFilename;
                scanner.lexicalAnalysis(programFilename);
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid option" << std::endl;
        }
    }
    

    return 0;
}
