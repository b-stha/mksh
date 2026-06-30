// Lexer for the shell. Tokenizes input using a state machine.

#include "shell/lexer.hpp"
#include <cctype>

const std::vector<std::string> Lexer::tokenizer(const std::string& input) {
    size_t i = 0;
    int state = 0;
    std::vector<std::string> lexemes;
    std::string currLex = "";

    while (i < input.size()) {
        switch (state) {
        case 0: // read character
            if (std::isspace(input[i])) { // skip whitespace
                state = 0; // stay in READ CHARACTER state
                i++;
            } 
            else if (input[i] == '\'' || input[i] == '\"') {
                state = 2; // go to STRING state
                currLex += input[i];
                i++;
            }
            else if (input[i] == '|' ||
                     input[i] == '&' ||
                     input[i] == '<' ||
                     input[i] == '>' ||
                     input[i] == '(' ||
                     input[i] == ')' ||
                     input[i] == ';' ) {
                state = 3; // go to OPERATOR state
                currLex += input[i];
                i++;
            }
            else { // any other character, part of a word
                state = 1; // go to WORD state
                currLex += input[i];
                i++;
            }
            break;
        case 1: // WORD state
            if (std::isspace(input[i])) {
                lexemes.push_back(currLex);
                currLex.clear();
                state = 0; // go back to READ CHARACTER state
                i++;
            }
            else if (input[i] == '\'' || input[i] == '\"') {
                state = 2; // go to STRING state
                currLex += input[i];
                i++;
            }
            else if (input[i] == '|' ||
                     input[i] == '&' ||
                     input[i] == '<' ||
                     input[i] == '>' ||
                     input[i] == '(' ||
                     input[i] == ')' ||
                     input[i] == ';' ) {
                state = 3; // go to OPERATOR state
                if (!currLex.empty()) {
                    lexemes.push_back(currLex);
                    currLex.clear();
                }
                currLex += input[i];
                i++;
            }
            else { // any other character, continue in WORD state
                currLex += input[i];
                i++;
            }
            break;
        case 2: // STRING state
            if (input[i] == '\'' || input[i] == '\"') {
                currLex += input[i];
                i++;
                state = 1; // go back to WORD state
            }
            else {
                currLex += input[i];
                i++;
            }
            break;
        case 3: // OPERATOR state
            while (i < input.size() && validOps.contains(currLex + input[i])) {
                currLex += input[i];
                i++;
            }
            lexemes.push_back(currLex);
            currLex.clear();
            state = 0; // go back to READ CHARACTER state
            break;
        }
    }
    if (!currLex.empty()) {
        lexemes.push_back(currLex);
    }
    return lexemes;
}