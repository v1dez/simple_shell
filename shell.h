#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* The environment */
extern char **environ;
/* Name of the program */
extern char *name;
/* History */
extern int history;

/**
 * struct list_s - structure type defining a linked list
 * @drty: directory path
 * @nts: pointer to another struct list_s
 */
typedef struct list_s
{
	char *drty;
	struct list_s *nts;
} list_t;

/**
 * struct builtin_t - new struct type defining builtin commands
 * @name: The name of the builtin command.
 * @j: A function pointer to the builtin command function
 */
typedef struct builtin_t
{
	char *name;
	int (*j)(char **argv, char **front);
} builtin_s;

/**
 * struct alias_s - new struct defining aliases
 * @name: name of the alias
 * @val: value of the alias
 * @nts: pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *nts;
} alias_t;

/* Function Prototypes */
char **switch_alias(char **args);
int shs_help(char **args, char **front);
char *get_loc(char *command);
int main(int argc, char *argv[]);

/* ... (Other function prototypes) ... */

#endif /* _SHELL_H_ */
