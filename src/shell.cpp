#include "shell/shell.hpp"
#include "shell/executor.hpp"
#include <iostream>

void Shell::run() {
    while (true) {
        std::cout << "mksh> ";
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