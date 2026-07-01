#include "shell/builtin.hpp"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <limits.h>

namespace mksh::builtin {
    bool isBuiltin(const std::string& command) {
        if (command == "cd" || command == "exit" || command == "help" || command == "pwd") {
            return true;
        }
        return false;
    }

    void run(const std::vector<mksh::Token>& args) {
        if (args.empty()) {
            return;
        }

        const std::string& cmd = args[0].value;

        if (cmd == "cd") {
            if (args.size() == 1) { // cd to home dir
                const char* home = getenv("HOME");
                if (home) {
                    chdir(home);
                }
            }
            else if (args.size() == 2) { // cd to specified dir
                if (chdir(args[1].value.c_str()) != 0) {
                    perror("cd");
                }
            }
            else { // too many arguments
                std::cerr << "cd: too many arguments" << std::endl;
            }
        }
        else if (cmd == "exit") {
            exit(0);
        } 
        else if (cmd == "help") {
            std::cout << "mksh: A simple shell implementation\n";
            std::cout << "Built-in commands:\n";
            std::cout << "  cd [dir]    Change the current directory to 'dir'\n";
            std::cout << "  exit       Exit the shell\n";
            std::cout << "  help       Display this help message\n";
            std::cout << "  pwd        Print the current working directory\n";
        }
        else if (cmd == "pwd") {
            char cwdPath[PATH_MAX];
            if (getcwd(cwdPath, sizeof(cwdPath)) != nullptr) {
                std::cout << cwdPath << std::endl;
            }
            else {
                perror("pwd");
            }
        }
    }
}

