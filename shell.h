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
/* Name of program */
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
 * @nts: pointer to another struct alias_t.
 */
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *nts;
} alias_t;

/* Global aliases linked list */
extern alias_t *aliases;

/*----------//My Function Prototypes\\----------*/
/*==============================================*/

al_inbuilt.c
int shs_alias(char **args, char __attribute__((__unused__)) **front);
void def_alias(char *var_name, char *val);
void writ_alias(alias_t *alias);
char **switch_alias(char **args, char **front);

built_in.c
int (*get_builtin(char *command))(char **args, char **front);
int shs_exit(char **args, char **front);
int shs_cd(char **args, char __attribute__((__unused__)) **front);
int shs_help(char **args, char __attribute__((__unused__)) **front);

builtin_aid.c
void aid_all(void);
void aid_alias(void);
void aid_cd(void);
void aid_exit(void);
void aiding_lp(void);

builtin_aid_2.c
void aid_env(void);
void aid_setenv(void);
void aid_unsetenv(void);
void aid_hist(void);

env_inbuilt.c
int shs_env(char **args, char __attribute__((__unused__)) **front);
int shs_setenv(char **args, char __attribute__((__unused__)) **front);
int shs_unsetenv(char **args, char __attribute__((__unused__)) **front);

env_iron.c
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

hand_err1.c
char *herr_env(char **args);
char *herr_1(char **args);
char *herr_2_exit(char **args);
char *herr_2_cd(char **args);
char *herr_2_syntax(char **args);

hand_err2.c
char *herr_iz(char **args);
char *herr_iz(char **args);

err.c
int nombre_len(int num);
char *_itoa(int num);
int create_err(char **args, int err);

getsline.c
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void as_lneptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getsline(char **lineptr, size_t *n, FILE *stream);

aidder.c
void fr_args(char **args, char **front);
char *get_pid(void);
char *get_env_val(char *beginning, int len);
void variable_repl(char **args, int *exe_ret);

aidders_2.c
void hand_line(char **lne, ssize_t read);
ssize_t isnew_len(char *lne);
void logl_ops(char *line, ssize_t *new_len);

in_aidders.c
char *get_args(char *lne, int *e_ret);
int call_args(char **args, char **front, int *e_ret);
int run_args(char **args, char **front, int *e_ret);
int hand_args(int *e_ret);
int check_args(char **args);

lnklist.c
alias_t *pl_alias_end(alias_t **ahe, char *nme, char *val);
void free_alias_list(alias_t *ahe);
list_t *pl_node_end(list_t **ahe, char *dir);
void free_list(list_t *ahe);

find.c
char *fill_pth_dir(char *pth);
list_t *get_pth_dir(char *pth);
char *get_loc(char *command);

main.c
void signal_handler(int signal);
int execute(char **args, char **front);
int main(int argc, char *argv[]);

proc_file_comm.c
int not_open(char *file_pth);
int proc_file_comm(char *file_path, int *exe_ret);

split.c
int tkn_len(char *str, char *del);
int count_tokens(char *str, char *del);
char **_strtok(char *line, char *del);

stringfxn1.c
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

stringfxn2.c
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif /* _SHELL_H_ */
