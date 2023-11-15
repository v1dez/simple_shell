#include "shell.h"

int shs_env(char **args, char __attribute__((__unused__)) **front);
int shs_setenv(char **args, char __attribute__((__unused__)) **front);
int shs_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shs_env - Prints the current environment
 * @args: An array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 * Return: If an error occurs - -1 status is thrown
 *	   Otherwise - 0 if no error occurs
 * Description: Prints one variable per line in the
 *              format 'variable'='value'
 */
int shs_env(char **args, char __attribute__((__unused__)) **front)
{
	int ind;
	char nic = '\n';

	if (!environ)
		return (-1);

	for (ind = 0; environ[ind]; ind++)
	{
		write(STDOUT_FILENO, environ[ind], _strlen(environ[ind]));
		write(STDOUT_FILENO, &nic, 1);
	}

	(void)args;
	return (0);
}

/**
 * shs_setenv - Changes or adds an environmental
 *	variable to the PATH of the shell Command
 * @args: An array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 * Description: args[1] is the name of the new or existing PATH variable
 *              args[2] is the value to set the new or changed variable to
 * Return: If an error occurs - -1
 *         Otherwise - 0
 */
int shs_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_val;
	size_t size;
	int ind;

	if (!args[0] || !args[1])
		return (create_err(args, -1));

	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_err
				(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_val);
		return (create_err(args, -1));
	}

	for (ind = 0; environ[ind]; ind++)
		new_environ[ind] = environ[ind];

	free(environ);
	environ = new_environ;
	environ[ind] = new_val;
	environ[ind + 1] = NULL;

	return (0);
}

/**
 * shs_unsetenv - Deletes an environmental variable from the PATH
 * @args: An array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 * Description: args[1] is the PATH variable to remove
 * Return: If an error occurs - -1
 *         Otherwise - 0
 */
int shs_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int ind, ind2;

	if (!args[0])
		return (create_err(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_err(args, -1));

	for (ind = 0, ind2 = 0; environ[ind]; ind++)
	{
		if (*env_var == environ[ind])
		{
			free(*env_var);
			continue;
		}
		new_environ[ind2] = environ[ind];
		ind2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
