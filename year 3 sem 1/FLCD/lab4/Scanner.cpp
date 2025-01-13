#include "Scanner.h"

// Input: Programs p1/p2/p3/p1error.txt and token.in
// Output: PIF.out, ST.out, message “lexically correct” or “lexical error + location”

Scanner::Scanner() { // constructor, initializes the symbol table and reserved words
    st = SymbolTable();
    faIdentifier = FA("FA_identifier.in");
    faIntegerConstant = FA("FA_integerConstant.in");
    
    std::ifstream f("token.in");
    if (!f.is_open()) {
        std::cerr << "Error opening file token.in" << std::endl;
        return;
    }
    
    char word[100];
    while (f >> word) tokens.insert(word);
    // replace <newline> and <space> with their actual values (a newline and a whitespace)
    tokens.insert("\n");
    tokens.insert(" ");
    tokens.erase("<newline>");
    tokens.erase("<space>");
    
    f.close();
}

void Scanner::print() {
    st.printIdentifiersLevelOrder(st.rootIdentifiers);
    st.printConstantsLevelOrder(st.rootConstants);
}

void Scanner::printReservedWords() {
    for (const auto& word : tokens) {
        std::cout << word << std::endl;
    }
}

// PIF.out will contain pairs of (token, position in ST)
// ST.out will contain the identifiers and constants in the symbol table, using the format: key index
/*
        b. Identifiers:
		A sequence of letters, underscores and digits; the first character is a letter; the rule is:
			identifier = letter | letter{letter | underscore | digit}
			letter = "a" | "b" | ... | "z" | "A" | "B" | ... | "Z"
			underscore = "_"
			digit = "0" | "1" | ... | "9"

        c. Constants:
		1. integer:
			nconst = "0" | n | "-"n
			n = nonzerodigit{digit}
			nonzerodigit = "1" | "2" | ... | "9"
		2. character:
			character = 'letter' | 'digit' | ' ' | '.' | ',' | '?' | '!' | '~' | '@' | '#' | '$' | '%' | '^' | '&' | '*' | '(' | ')' | '-' | '+' | '_' | '=' | ':' | '>' | '<'
		3. string:
			string = "{character}"
    	const = integer | character | string

    Constants and Identifiers will be stored in the symbol table, and their index will be stored in the PIF
*/

bool Scanner::isIdentifier(std::string word) {
    // check if the word is an identifier, using the rules defined above
    // if (word.size() == 0) return false;
    // if (!isalpha(word[0])) return false;
    // for (int i = 1; i < word.size(); i++) {
    //     if (!isalnum(word[i]) && word[i] != '_') return false;
    // }
    // return true;
    return faIdentifier.isAccepted(word);
}

bool Scanner::isStringConstant(std::string word) {
    // check if the word is a string constant, using the rules defined above
    if (word.size() < 2) return false;
    if (word[0] != '\"' || word[word.size() - 1] != '\"') return false;
    return true;
}

bool Scanner::isIntegerConstant(std::string word) {
    // check if word is constant, using the rules defined above
    // if (word.size() == 0) return false;
    // if (word[0] == '-') return false;
    // if (word[0] == '0' && word.size() > 1) return false;
    // if (word[0] == '0' && word.size() == 1) return true;
    // if (isdigit(word[0])) {
    //     for (int i = 1; i < word.size(); i++) {
    //         if (!isdigit(word[i])) return false;
    //     }
    //     return true;
    // }
    // // +0 and -0 are not valid constants. while +1 and -1 are
    // if (word[0] == '+' || word[0] == '-') {
    //     if (word.size() == 1) return false; // Single + or - is not valid
    //     if (word[1] == '0' && word.size() == 2) return false; // +0 and -0 are not valid
    //     for (int i = 1; i < word.size(); i++) {
    //         if (!isdigit(word[i])) return false; // All characters after the sign must be digits
    //     }
    //     return true;
    // }
    
    // // check if the word is a character
    // if (word.size() == 3 && word[0] == '\'' && word[2] == '\'') return true;
    // // check if the word is a string
    // if (word.size() >= 2 && word[0] == '\"' && word[word.size() - 1] == '\"') return true;
    // return false;
    return faIntegerConstant.isAccepted(word);
}

void Scanner::processToken(std::string &token, int line, std::ofstream &pif, SymbolTable &st) {
    if (tokens.find(token) != tokens.end()) {
        pif << token << " -1\n";
    } else if (isIdentifier(token)) {
        Node* x = st.putIdentifier(token);
        pif << token << " " << x->index << std::endl;
    } else if (isIntegerConstant(token)) {
        Node* x = st.putConstant(token);
        pif << token << " " << x->index << std::endl;
    } else if(isStringConstant(token)) {
        Node* x = st.putConstant(token);
        pif << token << " " << x->index << std::endl;
    } else {
        std::cerr << "Lexical error at line " << line << ": token `" << token << "`" << std::endl;
        pif << "Lexical error at line " << line << ": token `" << token << "`" << std::endl;
        exit(1);
    }
}

void Scanner::writeSymbolTable(SymbolTable &st, std::ofstream &stf) {
    std::vector<std::pair<std::string, int>> identifiers = st.getTableOfIdentifiers();
    for (auto& p : identifiers) {
        stf << p.first << " " << p.second << std::endl;
    }
    std::vector<std::pair<std::string, int>> constants = st.getTableOfConstants();
    for (auto& p : constants) {
        stf << p.first << " " << p.second << std::endl;
    }
}

void Scanner::lexicalAnalysis(std::string filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }
    std::ofstream pif("PIF.out");
    if (!pif.is_open()) {
        std::cerr << "Error opening file PIF.out" << std::endl;
        return;
    }
    std::ofstream stf("ST.out");
    if (!stf.is_open()) {
        std::cerr << "Error opening file ST.out" << std::endl;
        return;
    }

    int line = 1;
    char ch;
    bool insideString = false;
    std::string currentString;
    std::string currentToken;

    while (f.get(ch)) {
        if (insideString) {
            currentString += ch;
            if (ch == '\"') {
                // closing quote found, process the complete string
                insideString = false;
                if (isStringConstant(currentString)) {
                    Node* x = st.putConstant(currentString);
                    pif << currentString << " " << x->index << std::endl;
                } else {
                    std::cerr << "Lexical error at line " << line << ": string `" << currentString << "`" << std::endl;
                    pif << "Lexical error at line " << line << ": string `" << currentString << "`" << std::endl;
                    return;
                }
                currentString.clear();
            }
        } else {
            if (ch == '\"') {
                // Opening quote found, start a new string
                insideString = true;
                currentString = "\"";
            } else if (isspace(ch)) {
                if (ch == '\n') {
                    line++;
                }
                if (!currentToken.empty()) {
                    processToken(currentToken, line, pif, st);
                    currentToken.clear();
                }
            } else if (ispunct(ch)) {
                if (!currentToken.empty()) {
                    processToken(currentToken, line, pif, st);
                    currentToken.clear();
                }
                std::string charToString(1, ch);
                if (tokens.find(charToString) != tokens.end()) {
                    pif << charToString << " -1\n";
                } else {
                    std::cerr << "Lexical error at line " << line << ": token `" << charToString << "`" << std::endl;
                    pif << "Lexical error at line " << line << ": token `" << charToString << "`" << std::endl;
                    return;
                }
            } else {
                currentToken += ch;
            }
        }
    }

    if (!currentToken.empty()) {
        processToken(currentToken, line, pif, st);
        currentToken.clear();
    }

    writeSymbolTable(st, stf);

    f.close();
    pif.close();
    stf.close();
}
