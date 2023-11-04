My second group project

#0x16. C - Simple Shell

#C Group project Syscall

##Requirements

##General

Allowed editors: vi, vim, emacs

All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89

All your files should end with a new line

A README.md file, at the root of the folder of the project is mandatory

Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

Your shell should not have any memory leaks

No more than 5 functions per file

All your header files should be include guarded

Use system calls only when you need to (why?)

Write a README with the description of your project

You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

###More Info

###Output

Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.

The only difference is when you print an error, the name of the program must be equivalent to your argv[0]

List of allowed functions and system calls

access (man 2 access)

chdir (man 2 chdir)

close (man 2 close)

closedir (man 3 closedir)

execve (man 2 execve)

exit (man 3 exit)

_exit (man 2 _exit)

fflush (man 3 fflush)

fork (man 2 fork)

free (man 3 free)

getcwd (man 3 getcwd)

getline (man 3 getline)

getpid (man 2 getpid)

isatty (man 3 isatty)

kill (man 2 kill)

malloc (man 3 malloc)

open (man 2 open)

opendir (man 3 opendir)

perror (man 3 perror)

read (man 2 read)

readdir (man 3 readdir)

signal (man 2 signal)

stat (__xstat) (man 2 stat)

lstat (__lxstat) (man 2 lstat)

fstat (__fxstat) (man 2 fstat)

strtok (man 3 strtok)

wait (man 2 wait)

waitpid (man 2 waitpid)

wait3 (man 2 wait3)

wait4 (man 2 wait4)

write (man 2 write)

Compilation

Your shell will be compiled this way:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

###Testing

Your shell should work like this in interactive mode:

$ ./hsh

($) /bin/ls

hsh main.c shell.c

($)

($) exit

$

But also in non-interactive mode:

$ echo "/bin/ls" | ./hsh

hsh main.c shell.c test_ls_2

$

$ cat test_ls_2

/bin/ls

/bin/ls

$

$ cat test_ls_2 | ./hsh

hsh main.c shell.c test_ls_2

hsh main.c shell.c test_ls_2

$

Tasks

#0. Betty would be proud

##mandatory

Write a beautiful code that passes the Betty checks

###Repo:

GitHub repository: simple_shell

#1. Simple shell 0.1

##mandatory

Write a UNIX command line interpreter.

Usage: simple_shell

Your Shell should:

Display a prompt and wait for the user to type a command. A command line always ends with a new line.

The prompt is displayed again each time a command has been executed.

The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.

The command lines are made only of one word. No arguments will be passed to programs.

If an executable cannot be found, print an error message and display the prompt again.

Handle errors.

You have to handle the “end of file” condition (Ctrl+D)

You don’t have to:

use the PATH

implement built-ins

handle special characters : ", ', `, , *, &, #

be able to move the cursor

handle commands with arguments

execve will be the core part of your Shell, don’t forget to pass the environ to it…

###Repo:

GitHub repository: simple_shell

#2. Simple shell 0.2

##mandatory

Simple shell 0.1 +

Handle command lines with arguments

###Repo:

GitHub repository: simple_shell

#3. Simple shell 0.3

##mandatory

Simple shell 0.2 +

Handle the PATH

fork must not be called if the command doesn’t exist

###Repo:

GitHub repository: simple_shell

#4. Simple shell 0.4

##mandatory

Simple shell 0.3 +

Implement the exit built-in, that exits the shell

Usage: exit

You don’t have to handle any argument to the built-in exit

###Repo:

GitHub repository: simple_shell

#5. Simple shell 1.0

##mandatory

Simple shell 0.4 +

Implement the env built-in, that prints the current environment

###Repo:

GitHub repository: simple_shell

#6. Simple shell 0.1.1

##advanced

Simple shell 0.1 +

Write your own getline function

Use a buffer to read many chars at once and call the least possible the read system call

You will need to use static variables

You are not allowed to use getline

You don’t have to:

be able to move the cursor

###Repo:

GitHub repository: simple_shell

#7. Simple shell 0.2.1

##advanced

Simple shell 0.2 + You are not allowed to use strtok

###Repo: GitHub repository: simple_shell

#8. Simple shell 0.4.1

##advanced

Simple shell 0.4 +

handle arguments for the built-in exit

Usage: exit status, where status is an integer used to exit the shell

###Repo:

GitHub repository: simple_shell

#9. setenv, unsetenv

##advanced

Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands

setenv

Initialize a new environment variable, or modify an existing one

Command syntax: setenv VARIABLE VALUE

Should print something on stderr on failure

unsetenv

Remove an environment variable

Command syntax: unsetenv VARIABLE

Should print something on stderr on failure

###Repo: GitHub repository: simple_shell

#10. cd

##advanced

Simple shell 1.0 +

Implement the builtin command cd:

Changes the current directory of the process.

Command syntax: cd [DIRECTORY]

If no argument is given to cd the command must be interpreted like cd $HOME

You have to handle the command cd -

You have to update the environment variable PWD when you change directory

man chdir, man getcwd

###Repo:

GitHub repository: simple_shell

#11. ;

##advanced

Simple shell 1.0 +

Handle the commands separator ;

###Repo:

GitHub repository: simple_shell

#12. && and ||

##advanced

Simple shell 1.0 +

Handle the && and || shell logical operators

###Repo:

GitHub repository: simple_shell

#13. alias

##advanced

Simple shell 1.0 +

Implement the alias builtin command

Usage: alias [name[='value'] ...]

alias: Prints a list of all aliases, one per line, in the form name='value'

alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'

alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value

###Repo: GitHub repository: simple_shell

#14. Variables 

##advanced

Simple shell 1.0 +

Handle variables replacement

Handle the $? variable

Handle the $$ variable

###Repo:

GitHub repository: simple_shell

#15. Comments

##advanced

Simple shell 1.0 +

Handle comments (#)

###Repo:

GitHub repository: simple_shell

#16. File as input

##advanced

Simple shell 1.0 +

Usage: simple_shell [filename]

Your shell can take a file as a command line argument

The file contains all the commands that your shell should run before exiting

The file should contain one command per line

In this mode, the shell should not print a prompt and should not read from stdin

###Repo:

GitHub repository: simple_shell
