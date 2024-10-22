#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <string>
#include <iostream>

struct Node{
    std::string key;
    int index;
    Node* left;
    Node* right;
};

class SymbolTable{
private:
   public:
    Node* rootIdentifiers;
    Node* rootConstants; // we will have two trees, one for identifiers and one for constants
    int size, lastIdentifierIndex, lastConstantIndex; // size is the number of nodes in the tree, lastIdentifierIndex is the last index assigned to an identifier

    SymbolTable();
    Node* putIdentifier(std::string key);
    Node* getIdentifier(Node* x, std::string key); // x is from where we start the search
    Node* minIdentifier();
    Node* maxIdentifier();
    bool containsIdentifier(std::string key);

    Node* putConstant(std::string key);
    Node* getConstant(Node* x, std::string key); // x is from where we start the search
    Node* minConstant();
    Node* maxConstant();
    bool containsConstant(std::string key);

    void printIdentifiersPostOrder(Node* x);
    void printIdentifiersLevelOrder(Node* x);
    void printConstantsPostOrder(Node* x);
    void printConstantsLevelOrder(Node* x);
};

SymbolTable::SymbolTable(){
    rootIdentifiers = NULL;
    rootConstants = NULL;
    lastIdentifierIndex = 0;
    lastConstantIndex = 0;
    size = 0;
}

Node* SymbolTable::putIdentifier(std::string key){
    Node* x = rootIdentifiers; // we use x to traverse the tree
    Node* y = NULL; // this keeps track of the parent of x
    while(x != NULL){
        y = x;
        if(key.compare(x->key) < 0)    x = x->left;
        else if(key.compare(x->key) > 0)   x = x->right;
    }
    Node* z = new Node();
    z->key = key;
    z->index = lastIdentifierIndex++;
    z->left = NULL;
    z->right = NULL;
    if(y == NULL)   rootIdentifiers = z;
        else if(key.compare(y->key) < 0)    y->left = z;
            else    y->right = z;
    size++;
    return z;
}

Node* SymbolTable::getIdentifier(Node* x, std::string key){
    if(x == NULL) return NULL;
    if(key.compare(x->key) < 0)    return getIdentifier(x->left, key);
    else if(key.compare(x->key) > 0)   return getIdentifier(x->right, key);
    else    return x;
}

Node* SymbolTable::minIdentifier(){
    Node* x = rootIdentifiers;
    if(x == NULL) return NULL;
    while(x->left != NULL)  x = x->left;
    return x;
}

Node* SymbolTable::maxIdentifier(){
    Node* x = rootIdentifiers;
    if(x == NULL) return NULL;
    while(x->right != NULL) x = x->right;
    return x;
}

bool SymbolTable::containsIdentifier(std::string key){
    return getIdentifier(rootIdentifiers, key) != NULL;
}

Node* SymbolTable::putConstant(std::string key){
    Node* x = rootConstants; // we use x to traverse the tree
    Node* y = NULL; // this keeps track of the parent of x
    while(x != NULL){
        y = x;
        if(key.compare(x->key) < 0)    x = x->left;
        else if(key.compare(x->key) > 0)   x = x->right;
    }
    Node* z = new Node();
    z->key = key;
    z->index = lastConstantIndex++;
    z->left = NULL;
    z->right = NULL;
    if(y == NULL)   rootConstants = z;
        else if(key.compare(y->key) < 0)    y->left = z;
            else    y->right = z;
    size++;
    return z;
}

Node* SymbolTable::getConstant(Node* x, std::string key){
    if(x == NULL) return NULL;
    if(key.compare(x->key) < 0)    return getConstant(x->left, key);
    else if(key.compare(x->key) > 0)   return getConstant(x->right, key);
    else    return x;
}

Node* SymbolTable::minConstant(){
    Node* x = rootConstants;
    if(x == NULL) return NULL;
    while(x->left != NULL)  x = x->left;
    return x;
}

Node* SymbolTable::maxConstant(){
    Node* x = rootConstants;
    if(x == NULL) return NULL;
    while(x->right != NULL) x = x->right;
    return x;
}

bool SymbolTable::containsConstant(std::string key){
    return getConstant(rootConstants, key) != NULL;
}


void SymbolTable::printIdentifiersPostOrder(Node* x) {
    if (x == NULL) return;
    printIdentifiersPostOrder(x->left);
    printIdentifiersPostOrder(x->right);
    std::cout << x->key << " " << x->index << std::endl;
}

#include <queue>

void SymbolTable::printIdentifiersLevelOrder(Node* x) {
    if (x == NULL) return;
    std::queue<Node*> q;
    q.push(x);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->key << " " << current->index << std::endl;
        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
    }
}

void SymbolTable::printConstantsPostOrder(Node* x) {
    if (x == NULL) return;
    printIdentifiersPostOrder(x->left);
    printIdentifiersPostOrder(x->right);
    std::cout << x->key << " " << x->index << std::endl;
}

void SymbolTable::printConstantsLevelOrder(Node* x) {
    if (x == NULL) return;
    std::queue<Node*> q;
    q.push(x);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->key << " " << current->index << std::endl;
        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
    }
}

//void SymbolTable::printIdentifiers

int main(){
    SymbolTable st;
    // generate some random words and put them in the symbol table
    st.putIdentifier("test");
    st.putIdentifier("someOtherTest");
    st.putIdentifier("otherTest");
    st.putIdentifier("anotherTest");
    st.putIdentifier("zzz");
    st.putIdentifier("buggsBunny");
    st.putIdentifier("elmerFudd");
    st.putIdentifier("daffyDuck");
    st.putIdentifier("porkyPig");

    std::cout << "Identifiers post order:\n" << std::endl;
    st.printIdentifiersPostOrder(st.rootIdentifiers);
    std::cout << "Identifiers level order:\n" << std::endl;
    st.printIdentifiersLevelOrder(st.rootIdentifiers);

    st.putConstant("1");
    st.putConstant("2");
    st.putConstant("3");
    st.putConstant("4");
    st.putConstant("5");
    st.putConstant("a");
    st.putConstant("b");
    st.putConstant("c");
    st.putConstant("testString");
    st.putConstant("otherString");
    st.putConstant("8");
    st.putConstant("9");
    st.putConstant("anotherString");
    
    std::cout << "Constants post order:\n" << std::endl;
    st.printConstantsPostOrder(st.rootConstants);
    std::cout << "Constants level order:\n" << std::endl;
    st.printConstantsLevelOrder(st.rootConstants);
    return 0;
}