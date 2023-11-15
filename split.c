#include "shell.h"

/**
 * tkn_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @del: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the initial token pointed to by str.
 */
int tkn_len(char *str, char *del)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *del)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * int count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @del: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *del)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *del)
		{
			tokens++;
			index += tkn_len(str + index, del);
		}
	}

	return (tokens);
}

/**
 *  **_strtok - Tokenizes a string.
 * @line: The string.
 * @del: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *del)
{
	char **ptr;
	int index = 0, tokens, t, letters, k;

	tokens = count_tokens(line, del);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *del)
			index++;

		letters = tkn_len(line + index, del);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (k = 0; k < letters; k++)
		{
			ptr[t][k] = line[index];
			index++;
		}

		ptr[t][k] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
