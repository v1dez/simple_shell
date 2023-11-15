#include "shell.h"

/**
 * hand_line - Partitions a line read from standard inpu
 * @lne: A pointer to a line read from standard input
 * @read: The length of line.
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void hand_line(char **lne, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next;
	size_t i, j;
	ssize_t new_len;

	new_len = isnew_len(*lne);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *lne;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*lne);
	*lne = new_line;
}

/**
 * isnew_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @lne: The line to check.
 * Return: The new length of the line.
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t isnew_len(char *lne)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; lne[i]; i++)
	{
		current = lne[i];
		next = lne[i + 1];
		if (current == '#')
		{
			if (i == 0 || lne[i - 1] == ' ')
			{
				lne[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && lne[i - 1] != ' ' && lne[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (lne[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (lne[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logl_ops(&lne[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && lne[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logl_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logl_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

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
