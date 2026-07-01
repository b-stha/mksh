#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "token.hpp"

namespace mksh {
    class Lexer {
    public:
        const std::vector<std::string> tokenize(const std::string& input);
    private:
        std::vector<Token> tokens;
        static const std::unordered_map<std::string, TokenType> opTypes;
    };
}