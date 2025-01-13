#ifndef FA_H
#define FA_H

#include "ST.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <vector>

struct Transition{
    std::string from;
    std::string symbol;
    std::string to;
};

class FA{
    private:
        std::vector<std::string> states;
        std::vector<std::string> alphabet;
        std::vector<Transition> transitions;
        std::string initialState;
        std::vector<std::string> finalStates;
    public:
        FA(std::string filename);
        FA();
        void loadFromFile(std::string filename);
        bool isDeterministic();
        bool isAccepted(std::string sequence);
        std::set<std::string> getStates();
        std::set<std::string> getAlphabet();
        void print();
};


#endif