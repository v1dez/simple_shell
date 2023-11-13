#include "shell.h"

/**
 * deallocate_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void deallocate_args(char **args, char **front)
{
	size_t index;

	for (index = 0; args[index] || args[index + 1]; index++)
		free(args[index]);

	free(front);
}

/**
 * retrieve_process_id - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *retrieve_process_id(void)
{
	size_t index = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cannot read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[index] != ' ')
		index++;
	buffer[index] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_environment_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @length: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_environment_value(char *beginning, int length)
{
	char **var_address;
	char *replacement = NULL, *temp, *variable;

	variable = malloc(length + 1);
	if (!variable)
		return (NULL);
	variable[0] = '\0';
	_strncat(variable, beginning, length);

	var_address = get_environment_variable(variable);
	free(variable);
	if (var_address)
	{
		temp = *var_address;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * replace_variables - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exit_status: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and environmental variables
 *              preceded by $ with their corresponding value.
 */
void replace_variables(char **line, int *exit_status)
{
	int k, len, index = 0;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (k = 0; old_line[k]; k++)
	{
		if (old_line[k] == '$' && old_line[k + 1] &&
				old_line[k + 1] != ' ')
		{
			if (old_line[k + 1] == '$')
			{
				replacement = retrieve_process_id();
				index = k + 2;
			}
			else if (old_line[k + 1] == '?')
			{
				replacement = _itoa(*exit_status);
				index = k + 2;
			}
			else if (old_line[k + 1])
			{
				/* extract the variable name to search for */
				for (index = k + 1; old_line[index] &&
						old_line[index] != '$' &&
						old_line[index] != ' '; index++)
					;
				len = index - (k + 1);
				replacement = get_environment_value(&old_line[k + 1], len);
			}
			new_line = malloc(k + _strlen(replacement) +
					_strlen(&old_line[index]) + 1);
			if (!new_line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, k);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[index]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			k = -1;
		}
	}
}
