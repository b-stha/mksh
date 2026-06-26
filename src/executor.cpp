#include "shell/executor.hpp"
#include <cstdlib>

void Executor::execute(\const std::vector<std::string>& args) {
    if (command == "ls") {
        std::system("ls");
    }
}