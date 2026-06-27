#pragma once
#include <string>
#include <vector>
#include "shell/executor.hpp"

class Shell {
public:
    void run();
private:
    Executor executor;
    std::vector<std::string> tokenize(const std::string& input);
    std::string input;
};

