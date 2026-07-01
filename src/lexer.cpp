// Lexer definition for the shell. Tokenizes input using a state machine.

#include "shell/lexer.hpp"
#include <cctype>
#include <stdexcept>

const std::vector<mksh::Token> mksh::Lexer::tokenize(const std::string& input) {
    size_t i = 0;
    int state = 0;
    bool tokenInProg = false;
    std::vector<mksh::Token> tokens;
    std::string currLex = "";

    while (i < input.size()) {
        switch (state) {
        case 0: // read character
            if (std::isspace(input[i])) { // skip whitespace
                state = 0; // stay in READ CHARACTER state
                i++;
            } 
            else if (input[i] == '\'') {
                tokenInProg = true;
                state = 2; // go to SINGLE QUOTE state
                i++;
            }
            else if (input[i] == '\"') {
                tokenInProg = true;
                state = 3; // go to DOUBLE QUOTE state
                i++;
            }
            else if (input[i] == '|' ||
                     input[i] == '&' ||
                     input[i] == '<' ||
                     input[i] == '>' ||
                     input[i] == '(' ||
                     input[i] == ')' ||
                     input[i] == ';' ) {
                tokenInProg = true;
                state = 4; // go to OPERATOR state
            }
            else { // any other character, part of a word
                tokenInProg = true;
                state = 1; // go to WORD state
                currLex += input[i];
                i++;
            }
            break;
        case 1: // WORD state
            if (std::isspace(input[i]) && tokenInProg) {
                tokens.push_back(mksh::Token{currLex, mksh::TokenType::WORD});
                currLex.clear();
                tokenInProg = false;
                state = 0; // go back to READ CHARACTER state
                i++;
            }
            else if (input[i] == '\'') {
                state = 2; // go to SINGLE QUOTE state
                i++;
            }
            else if (input[i] == '\"') {
                state = 3; // go to DOUBLE QUOTE state
                i++;
            }
            else if (input[i] == '|' ||
                     input[i] == '&' ||
                     input[i] == '<' ||
                     input[i] == '>' ||
                     input[i] == '(' ||
                     input[i] == ')' ||
                     input[i] == ';' ) {
                state = 4; // go to OPERATOR state
                if (tokenInProg) {
                    tokens.push_back(mksh::Token{currLex, mksh::TokenType::WORD});
                    currLex.clear();
                    tokenInProg = false;
                }
            }
            else { // any other character, continue in WORD state
                currLex += input[i];
                i++;
            }
            break;
        case 2: // SINGLE QUOTE state
            if (input[i] == '\'') {
                state = 1; // go back to WORD state
                i++;
            }
            else {
                currLex += input[i];
                i++;
            }
            break;
        case 3: // DOUBLE QUOTE state
            if (input[i] == '\"') {
                state = 1; // go back to WORD state
                i++;
            }
            else {
                currLex += input[i];
                i++;
            }
            break;

        case 4: // OPERATOR state
            if (!tokenInProg) {
                tokenInProg = true;
            }
            currLex += input[i]; // add the first character of the operator
            i++;
            while (i < input.size() && opTypes.contains(currLex + input[i])) {
                currLex += input[i];
                i++;
            }
            if (tokenInProg) {
                tokens.push_back(mksh::Token{currLex, opTypes.at(currLex)});
                tokenInProg = false;
                currLex.clear();
            }
            state = 0; // go back to READ CHARACTER state
            break;
        }
    }

    if (state == 2) {
        // Handle unclosed single quote
        throw std::runtime_error("Unclosed single quote in input");
    }
    else if (state == 3) {
        // Handle unclosed double quote
        throw std::runtime_error("Unclosed double quote in input");
    }

    if (tokenInProg) {
        tokens.push_back(mksh::Token{currLex, mksh::TokenType::WORD});
        tokenInProg = false;
        currLex.clear();
    }
    return tokens;
}

const std::unordered_map<std::string, mksh::TokenType> mksh::Lexer::opTypes = {
    {"|", mksh::TokenType::PIPE},
    {"||", mksh::TokenType::OR},
    {"&", mksh::TokenType::BACKGROUND},
    {"&&", mksh::TokenType::AND},
    {"<", mksh::TokenType::REDIRECT_IN},
    {"<<", mksh::TokenType::HEREDOC},
    {"<<<", mksh::TokenType::HERESTRING},
    {">", mksh::TokenType::REDIRECT_OUT},
    {">>", mksh::TokenType::REDIRECT_APPEND},
    {">|", mksh::TokenType::CLOBBER},
    {"(", mksh::TokenType::LPAREN},
    {")", mksh::TokenType::RPAREN},
    {";", mksh::TokenType::SEMICOLON}
};