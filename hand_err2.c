#include "shell.h"

/**
 * herr_126 - Creates an error message for permission denied failures
 * @args: An array of arguments passed to the command
 * Return: The error string
 */
char *herr_126(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(herr, name);
	_strcat(herr, ": ");
	_strcat(herr, hist_str);
	_strcat(herr, ": ");
	_strcat(herr, args[0]);
	_strcat(herr, ": Permission denied\n");

	free(history_str);
	return (error);
}

/**
 * herr_127 - Creates an error message for command not found failures
 * @args: An array of arguments passed to the command
 * Return: The error string
 */
char *herr_127(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(history);
	if (!history_str)
		return (NULL);

	len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(history_str);
	return (error);
}
