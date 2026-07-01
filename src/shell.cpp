#include "shell/shell.hpp"
#include "shell/executor.hpp"
#include <iostream>
#include <limits.h>
#include <unistd.h>

void mksh::Shell::run() {
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

        std::vector<mksh::Token> args;
        try {
            args = lexer.tokenize(input);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
        
        for (const auto& arg : args) {
            std::cout << arg.value << ", " << static_cast<int>(arg.type) << " " << std::endl;
        }
        executor.execute(args);
    }
}