#include "shell.h"

/**
 * format_input - Partitions a line read from standard input as needed or described.
 * @input: A pointer to a line read from standard input.
 * @read_len: The length of the input line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void format_input(char **input, ssize_t read_len)
{
	char *old_input, *new_input;
	char previous, current, next;
	size_t i, j;
	ssize_t new_len;

	new_len = get_formatted_length(*input);
	if (new_len == read_len - 1)
		return;
	new_input = malloc(new_len + 1);
	if (!new_input)
		return;
	j = 0;
	old_input = *input;
	for (i = 0; old_input[i]; i++)
	{
		current = old_input[i];
		next = old_input[i + 1];
		if (i != 0)
		{
			previous = old_input[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_input[j++] = ' ';
					new_input[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_input[j++] = ';';
					new_input[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_input[j++] = ' ';
				new_input[j++] = ';';
				if (next != ' ')
					new_input[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_input[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_input[j++] = '&';
					new_input[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_input[j++] = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_input[j++] = '|';
					new_input[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_input[i - 1] != ' ')
				new_input[j++] = ' ';
			new_input[j++] = ';';
			if (next != ' ' && next != ';')
				new_input[j++] = ' ';
			continue;
		}
		new_input[j++] = old_input[i];
	}
	new_input[j] = '\0';

	free(*input);
	*input = new_input;
}

/**
 * get_formatted_length - Gets the new length of an input partitioned
 *                        by ";", "||", "&&&", or "#".
 * @input: The input to check.
 *
 * Return: The new length of the input.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */
ssize_t get_formatted_length(char *input)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; input[i]; i++)
	{
		current = input[i];
		next = input[i + 1];
		if (current == '#')
		{
			if (i == 0 || input[i - 1] == ' ')
			{
				input[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && input[i - 1] != ' ' && input[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (input[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (input[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				check_logical_ops(&input[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && input[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * check_logical_ops - Checks an input for logical operators "||" or "&&".
 * @input: A pointer to the character to check in the input.
 * @new_len: Pointer to new_len in get_formatted_length function.
 */
void check_logical_ops(char *input, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(input - 1);
	current = *input;
	next = *(input + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
