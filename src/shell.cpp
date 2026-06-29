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
        std::cout << "mksh: " << cwdPath << "> ";
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }

        std::vector<std::string> args;
        args = tokenize(input);
        executor.execute(args);
    }
}

std::vector<std::string> Shell::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    size_t left = 0, right = 0;

    while (right < input.length()) {
        if (std::isspace(input[right])) {
            if (left != right) {
                tokens.push_back(input.substr(left, right - left));
            }
            left = right + 1;
        }
        right++;
    }

    if (left != right) {
        tokens.push_back(input.substr(left, right - left));
    }

    return tokens;
}