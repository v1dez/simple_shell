#include "shell.h"

/**
 * _copyenv - Creates a copy of the environment
 * Return: If an error occurs - NULL
 *         O/w - a double pointer to the new copy
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int ind;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		new_environ[ind] = malloc(_strlen(environ[ind]) + 1);

		if (!new_environ[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(new_environ[ind]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[ind], environ[ind]);
	}
	new_environ[ind] = NULL;

	return (new_environ);
}

/**
 * free_env - Frees the the environment copy
 */
void free_env(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH
 * @var: The name of the environmental variable to get from PATH
 * Return: If the environmental variable does not exist - NULL
 *         Otherwise - a pointer to the environmental variabl
 */
char **_getenv(const char *var)
{
	int ind, len;

	len = _strlen(var);
	for (ind = 0; environ[ind]; ind++)
	{
		if (_strncmp(var, environ[ind], len) == 0)
			return (&environ[ind]);
	}

	return (NULL);
}
