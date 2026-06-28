#include "shell/executor.hpp"
#include "shell/builtin.hpp"
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

void Executor::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        return;
    }


    if (mksh::builtin::isBuiltin(args[0])) { // check if builtin
        // execute builtin command
        mksh::builtin::run(args);
    }


    // execute command externally
    pid_t pid = fork();

    if (pid < 0) { // fork failure
        std::cerr << "Fork failed." << std::endl;
    }
    else if (pid == 0) { // child process
        std::vector<char*> c_args;
        for (const auto& arg : args) {
            c_args.push_back(const_cast<char*>(arg.c_str()));
        }
        c_args.push_back(nullptr); // execvp requires a null-terminated array
        execvp(c_args[0], c_args.data());
        perror(c_args[0]);
        _exit(EXIT_FAILURE);
    }
    else { // parent process
        int status;
        waitpid(pid, &status, 0);
    }
}