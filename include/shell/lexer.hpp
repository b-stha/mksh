#pragma once
#include <vector>
#include <string>
#include <unordered_set>

class Lexer {
public:
    const std::vector<std::string> tokenize(const std::string& input);
private:
    std::unordered_set<std::string> validOps = {"|", "||", "&", "&&", "<", "<<", "<<<", ">", ">>", ">|", "(", ")", ";"};
};