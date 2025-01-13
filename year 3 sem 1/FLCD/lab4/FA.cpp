#include "FA.h"

FA::FA(std::string filename) {
    loadFromFile(filename);
}

FA::FA() {
    ;
}

void FA::loadFromFile(std::string filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(f, line)) {
        if (line.find("states") != std::string::npos) {
            std::string states = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::string state;
            for (char c : states) {
                if (c == ',') {
                    this->states.push_back(state);
                    state.clear();
                } else if (c != ' ') {
                    state += c;
                }
            }
            this->states.push_back(state);
        } else if (line.find("epsilon") != std::string::npos) {
            std::string alphabet = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::string symbol;
            for (char c : alphabet) {
                if (c == ',') {
                    this->alphabet.push_back(symbol);
                    symbol.clear();
                } else if (c != ' ') {
                    symbol += c;
                }
            }
            this->alphabet.push_back(symbol);
        } else if (line.find("initial") != std::string::npos) {
            this->initialState = line.substr(line.find("=") + 2);
        } else if (line.find("final") != std::string::npos) {
            std::string finalStates = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::string state;
            for (char c : finalStates) {
                if (c == ',') {
                    this->finalStates.push_back(state);
                    state.clear();
                } else if (c != ' ') {
                    state += c;
                }
            }
            this->finalStates.push_back(state);
        } else if (line.find("delta") != std::string::npos) {
            std::string transitions = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::string transition;
            bool inTransition = false;
            for (char c : transitions) {
                if (c == '(') {
                    inTransition = true;
                    transition.clear();
                } else if (c == ')') {
                    inTransition = false;
                    Transition t;
                    size_t pos1 = transition.find(',');
                    size_t pos2 = transition.find(',', pos1 + 1);
                    t.from = transition.substr(0, pos1);
                    t.symbol = transition.substr(pos1 + 1, pos2 - pos1 - 1);
                    t.to = transition.substr(pos2 + 1);
                    this->transitions.push_back(t);
                } else if (inTransition && c != ' ') {
                    transition += c;
                }
            }
        }
    }
}

void FA::print() {
    std::cout << "States: ";
    for (const std::string& state : this->states) {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    std::cout << "Alphabet: ";
    for (const std::string& symbol : this->alphabet) {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "Transitions: ";
    for (const Transition& t : this->transitions) {
        std::cout << "(" << t.from << ", " << t.symbol << ", " << t.to << ") ";
    }
    std::cout << std::endl;

    std::cout << "Initial state: " << this->initialState << std::endl;

    std::cout << "Final states: ";
    for (const std::string& state : this->finalStates) {
        std::cout << state << " ";
    }
    std::cout << std::endl;
}

bool FA::isDeterministic(){
    // check if the FA is deterministic
    // for each transition, the pair (from, symbol) should be unique
    std::map<std::pair<std::string, std::string>, std::string> m;
    for (Transition t : this->transitions) {
        if (m.find(std::make_pair(t.from, t.symbol)) != m.end()) {
            return false;
        }
        m[std::make_pair(t.from, t.symbol)] = t.to;
    }
    return true;
}

bool FA::isAccepted(std::string sequence){
    // check if the sequence is accepted by the FA
    std::string currentState = this->initialState;
    for (char c : sequence) {
        std::string symbol;
        symbol += c;
        bool found = false;
        for (Transition t : this->transitions) {
            if (t.from == currentState && t.symbol == symbol) {
                currentState = t.to;
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    for (std::string state : this->finalStates) {
        if (currentState == state) {
            return true;
        }
    }
    return false;
}