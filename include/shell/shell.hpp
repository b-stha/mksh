#pragma once
#include <string>
#include <vector>
#include "shell/executor.hpp"

class Shell {
public:
    void run();
private:
    Executor executor;
    std::string input;
};

