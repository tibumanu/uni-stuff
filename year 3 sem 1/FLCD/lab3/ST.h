#ifndef ST_H
#define ST_H

#include <string>
#include <iostream>
#include <queue>
#include <vector>

struct Node {
    std::string key;
    int index;
    Node* left;
    Node* right;
};

class SymbolTable {
public:
    Node* rootIdentifiers;
    Node* rootConstants;
    int size, lastIdentifierIndex, lastConstantIndex;

    SymbolTable();

    Node* getRootIdentifiers() const;
    Node* getRootConstants() const;
    
    Node* putIdentifier(std::string key);
    Node* getIdentifier(Node* x, std::string key);
    Node* minIdentifier();
    Node* maxIdentifier();
    bool containsIdentifier(std::string key);

    Node* putConstant(std::string key);
    Node* getConstant(Node* x, std::string key);
    Node* minConstant();
    Node* maxConstant();
    bool containsConstant(std::string key);

    void printIdentifiersPostOrder(Node* x);
    void printIdentifiersLevelOrder(Node* x);
    void printConstantsPostOrder(Node* x);
    void printConstantsLevelOrder(Node* x);

    std::vector<std::pair<std::string, int>> getTableOfIdentifiers();
    std::vector<std::pair<std::string, int>> getTableOfConstants();
};

#endif // ST_H