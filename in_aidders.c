#include "shell.h"

/**
 * get_input - Gets a command from standard input.
 * @line: A buffer to store the command to improve performance.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *lne, int *e_ret);
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_input(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * separate_and_execute - Partitions operators from commands and calls them.
 * @commands: An array of commands.
 * @front: A double pointer to the beginning of commands.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_args(char **args, char **front, int *e_ret);
{
	int ret, index;

	if (!commands[0])
		return (*exe_ret);
	for (index = 0; commands[index]; index++)
	{
		if (_strncmp(commands[index], "||", 2) == 0)
		{
			free(commands[index]);
			commands[index] = NULL;
			commands = replace_aliases(commands);
			ret = execute_commands(commands, front, exe_ret);
			if (*exe_ret != 0)
			{
				commands = &commands[++index];
				index = 0;
			}
			else
			{
				for (index++; commands[index]; index++)
					free(commands[index]);
				return (ret);
			}
		}
		else if (_strncmp(commands[index], "&&", 2) == 0)
		{
			free(commands[index]);
			commands[index] = NULL;
			commands = replace_aliases(commands);
			ret = execute_commands(commands, front, exe_ret);
			if (*exe_ret == 0)
			{
				commands = &commands[++index];
				index = 0;
			}
			else
			{
				for (index++; commands[index]; index++)
					free(commands[index]);
				return (ret);
			}
		}
	}
	commands = replace_aliases(commands);
	ret = execute_commands(commands, front, exe_ret);
	return (ret);
}

/**
 * execute_commands - Calls the execution of a command.
 * @commands: An array of commands.
 * @front: A double pointer to the beginning of commands.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command on the shell history.
 */
int run_args(char **args, char **front, int *e_ret);
{
	int ret, j;
	int (*builtin)(char **commands, char **front);

	builtin = get_builtin(commands[0]);

	if (builtin)
	{
		ret = builtin(commands + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(commands, front);
		ret = *exe_ret;
	}

	history++;

	for (j = 0; commands[j]; j++)
		free(commands[j]);

	return (ret);
}

/**
 * process_commands - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         Otherwise - The exit value of the last executed command.
 */
int hand_args(int *e_ret);
{
	int ret = 0, index;
	char **commands, *line = NULL, **front;

	line = get_input(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	commands = _strtok(line, " ");
	free(line);
	if (!commands)
		return (ret);
	if (check_commands(commands) != 0)
	{
		*exe_ret = 2;
		free_commands(commands, commands);
		return (*exe_ret);
	}
	front = commands;

	for (index = 0; commands[index]; index++)
	{
		if (_strncmp(commands[index], ";", 1) == 0)
		{
			free(commands[index]);
			commands[index] = NULL;
			ret = separate_and_execute(commands, front, exe_ret);
			commands = &commands[++index];
			index = 0;
		}
	}
	if (commands)
		ret = separate_and_execute(commands, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_commands - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @commands: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2 as error status.
 *         Otherwise - 0 as error status.
 */
int check_args(char **args);
{
	size_t j;
	char *cur, *nex;

	for (j = 0; commands[j]; j++)
	{
		cur = commands[j];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (j == 0 || cur[1] == ';')
				return (create_error(&commands[j], 2));
			nex = commands[j + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&commands[j + 1], 2));
		}
	}
	return (0);
}
