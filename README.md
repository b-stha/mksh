# mksh

mksh (pronounced "mash") is a small shell environment, developed as an application of my learning in my compilers and operating system courses.

## Supported commands

Current built-in commands include:

- cd
- pwd
- help
- exit

mksh also supports external commands using forked processes, such as 'ls' and 'grep'.

## headers

### main

- entrypoint for main shell program
- creates and runs an instance of shell object

### shell

- contains the main REPL for user I/O
- currently utilizes its own tokenizing logic (soon to be moved to the lexer)

### executor

- currently only takes in user commands and arguments to be executed
- checks if user command is a built in or not
- executes external binaries through fork()

### builtin

- currently a namespace containing functions for built-in logic
- may be converted to a proper object later

### TBA: lexer

### TBA: parser

### TBA: AST
