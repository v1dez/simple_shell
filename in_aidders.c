#include "shell.h"

/**
 * get_args - Gets a command from standard input.
 * @lne: A buffer to store the command to improve perfomance.
 * @e_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *lne, int *e_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (lne)
		free(lne);

	read = _getsline(&lne, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(lne, e_ret));
	}

	lne[read - 1] = '\0';
	variable_repl(&lne, e_ret);
	hand_line(&lne, read);

	return (lne);
}

/**
 * call_args - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args
 * @e_ret: The return value of the parent process' last executed command
 * Return: The return value of the last executed command
 */
int call_args(char **args, char **front, int *e_ret)
{
	int rt, ind;

	if (!args[0])
		return (*e_ret);
	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], "||", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = repl_alias(args);
			rt = run_args(args, front, e_ret);
			if (*e_ret != 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (rt);
			}
		}
		else if (_strncmp(args[ind], "&&", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = repl_alias(args);
			rt = run_args(args, front, e_ret);
			if (*e_ret == 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (rt);
			}
		}
	}
	args = repl_alias(args);
	rt = run_args(args, front, e_ret);
	return (rt);
}

/**
 * run_args - Calls the execution of a command
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 * @e_ret: The return value of the parent process'd command
 * Return: The return value of the last executed command on the sh
 */
int run_args(char **args, char **front, int *e_ret)
{
	int rt, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		rt = builtin(args + 1, front);
		if (rt != EXIT)
			return (rt);
	}
	else
	{
		*e_ret = execute(args, front);
		rt = *e_ret;
	}

	history++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (rt);
}

/**
 * hand_args - Gets, calls, and runs the execution of a command.
 * @e_ret: The return value of the parent process' last exe
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int hand_args(int *e_ret)
{
	int rt = 0, ind;
	char **args, *line = NULL, **front;

	line = get_args(line, e_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (rt);
	if (check_args(args) != 0)
	{
		*e_ret = 2;
		fr_args(args, args);
		return (*e_ret);
	}
	front = args;

	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], ";", 1) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			rt = call_args(args, front, e_ret);
			args = &args[++ind];
			ind = 0;
		}
	}
	if (args)
		rt = call_args(args, front, e_ret);

	free(front);
	return (rt);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid positi
 *	   Otherwise - 0 as error status.
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_err(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_err(&args[i + 1], 2));
		}
	}
	return (0);
}
