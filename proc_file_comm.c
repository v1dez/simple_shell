#include "shell.h"

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a can't open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */
int cant_open(char *file_path)
{
	/* ... (no changes to this function) */
}

/**
 * proc_file_comm - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If the file couldn't be opened - 127.
 *         If malloc fails - -1.
 *         Otherwise, the return value of the last command ran.
 */
int proc_file_comm(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, j;
	size_t line_size = 0;
	size_t old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	history = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}

	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);

	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);

		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);

	for (j = 0; line[j] == '\n'; j++)
		line[j] = ' ';

	for (; j < line_size; j++)
	{
		if (line[j] == '\n')
		{
			line[j] = ';';
			for (j += 1; j < line_size && line[j] == '\n'; j++)
				line[j] = ' ';
		}
	}

	variable_repl(&line, exe_ret);
	hand_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);

	if (!args)
		return (0);

	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}

	front = args;

	for (j = 0; args[j]; j++)
	{
		if (_strncmp(args[j], ";", 1) == 0)
		{
			free(args[j]);
			args[j] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++j];
			j = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
