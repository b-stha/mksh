#pragma once
#include <string>
#include <vector>
#include "shell/executor.hpp"
#include "shell/lexer.hpp"

class Shell {
public:
    void run();
private:
    Executor executor;
    std::string input;
    Lexer lexer;
};

