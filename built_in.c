#include "shell.h"

/**
 * get_builtin - Matches a command with a corresponding
 * @command: The command to match
 * Return: A function pointer to the corresponding builtin
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_s funcs[] = {
		{ "exit", shs_exit },
		{ "env", shs_env },
		{ "setenv", shs_setenv },
		{ "unsetenv", shs_unsetenv },
		{ "cd", shs_cd },
		{ "alias", shs_alias },
		{ "help", shs_help },
		{ NULL, NULL }
	};
	int t;

	for (t = 0; funcs[t].name; t++)
	{
		if (_strcmp(funcs[t].name, command) == 0)
			break;
	}
	return (funcs[t].j);
}

/**
 * shs_exit - Causes normal process termination
 * @args: An array of arguments containing the exit value
 * @front: A double pointer to the beginning of args
 * Return: If there are no arguments - -3
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int shs_exit(char **args, char **front)
{
	int t, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			t = 1;
			len_of_int++;
		}
		for (; args[0][t]; t++)
		{
			if (t <= len_of_int && args[0][t] >= '0' && args[0][t] <= '9')
				num = (num * 10) + (args[0][t] - '0');
			else
				return (create_err(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_err(--args, 2));
	args -= 1;
	fr_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shs_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shs_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_err(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_err(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shs_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shs_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shs_help - Displays information about shellby builtin commands
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shs_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		aid_all();
	else if (_strcmp(args[0], "alias") == 0)
		aid_alias();
	else if (_strcmp(args[0], "cd") == 0)
		aid_cd();
	else if (_strcmp(args[0], "exit") == 0)
		aid_exit();
	else if (_strcmp(args[0], "env") == 0)
		aid_env();
	else if (_strcmp(args[0], "setenv") == 0)
		aid_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		aid_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		aiding_lp();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
