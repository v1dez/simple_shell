#include "shell.h"

/**
 * nombre_len - Counts the digit length of a number
 * @num: The number to measure
 * Return: The digit length
 */
int nombre_len(int num)
{
	unsigned int nm1;
	int len = 1;

	if (num < 0)
	{
		len++;
		nm1 = num * -1;
	}
	else
	{
		nm1 = num;
	}
	while (nm1 > 9)
	{
		len++;
		nm1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string to enable manipulation
 * @num: The integer
 * Return: The converted string
 */
char *_itoa(int num)
{
	char *buffer;
	int len = nombre_len(num);
	unsigned int nm1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		nm1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		nm1 = num;
	}

	len--;
	do {
		buffer[len] = (nm1 % 10) + '0';
		nm1 /= 10;
		len--;
	} while (nm1 > 0);

	return (buffer);
}


/**
 * create_err - Writes a custom error message t
 * ostderr that conforms to shell standards
 * @args: An array of arguments passed to the function
 * @err: The error value
 * Return: The error value
 */
int create_err(char **args, int err)
{
	char *error = NULL;

	switch (err)
	{
	case -1:
		error = herr_env(args);
		break;
	case 1:
		error = herr_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = herr_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = herr_2_syntax(args);
		else
			error = herr_2_cd(args);
		break;
	case 126:
		err = error_126(args);
		break;
	case 127:
		err = error_127(args);
		break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	return (err);
}
