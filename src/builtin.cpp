#include "include/shell/builtin.hpp"
#include <unistd.h>
#include <cstdlib>
#include <iostream>

namespace mksh::builtin {
    bool isBuiltin(const std::string& command) {
        if (command == "cd" || command == "exit" || command == "help" || command == "pwd") {
            return true;
        }
        return false;
    }

    void run(const std::vector<std::string>& args) {
        if (args.empty()) {
            return;
        }

        const std::string& cmd = args[0];

        if (cmd == "cd") {
            if (args.size() == 1) { // cd to home dir
                const char* home = getenv("HOME");
                if (home) {
                    chdir(home);
                }
            }
            else if (args.size() == 2) { // cd to specified dir
                if (chdir(args[1].c_str()) != 0) {
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

        }
        else if (cmd == "pwd") {

        }
    }
}

