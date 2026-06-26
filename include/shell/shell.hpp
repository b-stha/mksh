#pragma once
#include <string>
#include <vector>
class Shell {
public:
    void run();
private:
    std::vector<std::string> tokenize(const std::string& input);
    std::string input;
};

