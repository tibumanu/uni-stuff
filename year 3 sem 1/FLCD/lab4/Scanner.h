#ifndef SCANNER_H
#define SCANNER_H

#include "ST.h"
#include "FA.h"
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <vector>

class Scanner {
private:
    SymbolTable st; // symbol table, implemented using a binary search tree
    std::set<std::string> tokens; // set of reserved words

    FA faIdentifier;
    FA faIntegerConstant;

public:
    Scanner(); // constructor, initializes the symbol table and reserved words
    void print();
    void printReservedWords();
    bool isIdentifier(std::string word);
    bool isIntegerConstant(std::string word);
    bool isStringConstant(std::string word);
    void processToken(std::string &token, int line, std::ofstream &pif, SymbolTable &st);
    void writeSymbolTable(SymbolTable &st, std::ofstream &stf);
    void lexicalAnalysis(std::string filename);
};

#endif // SCANNER_H
