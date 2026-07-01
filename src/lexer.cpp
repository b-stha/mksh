// Lexer definition for the shell. Tokenizes input using a state machine.

#include "shell/lexer.hpp"
#include <cctype>

const std::vector<mksh::Token> mksh::Lexer::tokenize(const std::string& input) {
    size_t i = 0;
    int state = 0;
    std::vector<mksh::Token> tokens;
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
                tokens.push_back(mksh::Token{currLex, mksh::TokenType::WORD});
                currLex.clear();
                state = 0; // go back to READ CHARACTER state
                i++;
            }
            else if (input[i] == '\'' || input[i] == '\"') {
                state = 2; // go to STRING state
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
                    tokens.push_back(mksh::Token{currLex, mksh::TokenType::WORD});
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
                state = 1; // go back to WORD state
                i++;
            }
            else {
                currLex += input[i];
                i++;
            }
            break;
        case 3: // OPERATOR state
            while (i < input.size() && opTypes.contains(currLex + input[i])) {
                currLex += input[i];
                i++;
            }
            tokens.push_back(mksh::Token{currLex, opTypes.at(currLex)});
            currLex.clear();
            state = 0; // go back to READ CHARACTER state
            break;
        }
    }
    if (!currLex.empty()) {
        tokens.push_back(mksh::Token{currLex, mksh::TokenType::WORD});
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