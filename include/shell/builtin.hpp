#pragma once
#include <string>
#include <vector>
#include "token.hpp"

namespace mksh::builtin {
    bool isBuiltin(const std::string& command); // check if command is a builtin
    void run(const std::vector<mksh::Token>& args); // run builtin
}