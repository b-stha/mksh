#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "token.hpp"

namespace mksh {
    class Lexer {
    public:
        const std::vector<Token> tokenize(const std::string& input);
    private:
        static const std::unordered_map<std::string, TokenType> opTypes;
    };
}