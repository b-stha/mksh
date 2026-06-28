#pragma once
#include <string>
#include <vector>

namespace mksh::builtin {
    bool isBuiltin(const std::string& command); // check if command is a builtin
    void run(const std::vector<std::string>& args); // run builtin
}