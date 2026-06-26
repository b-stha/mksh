#include "shell/shell.hpp"
#include <iostream>

void Shell::run() {
    while (true) {
        std::cout << "mksh> ";
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }

        std::cout << "You entered: " << input << std::endl;
    }
}
