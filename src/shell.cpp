#include "shell/shell.hpp"
#include "shell/executor.hpp"
#include <iostream>
#include <limits.h>
#include <unistd.h>

void Shell::run() {
    while (true) {
        char cwdPath[PATH_MAX];
        if (getcwd(cwdPath, sizeof(cwdPath)) == nullptr) {
            perror("pwd");
        }
        std::cout << "mksh: " << cwdPath << " > ";
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }

        std::vector<std::string> args;
        args = lexer.tokenize(input);
        for (const auto& arg : args) {
            std::cout << arg << " " << std::endl;
        }
        executor.execute(args);
    }
}