# mksh grammar poc

## first it

implementation of simple commands. commands are words separated by one or more whitespaces. commands are followed by arguments.

line: command | empty
command: word+
argument: word following command
word: sequence of characters without whitespace

ex:

- ls
- ls -l
- echo hello
- pwd
- cd ..
- exit
  