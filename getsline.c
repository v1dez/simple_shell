#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: A pointer to the memory previously allocated
 * @old_size: The size in bytes of the allocated space for ptr
 * @new_size: The size in bytes for the new memory block
 * Return: If new_size == old_size - ptr
 *         If new_size == 0 and ptr is not NULL - NULL
 *         Otherwise - a pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *meme;
	char *ptr_copy, *filler;
	unsigned int ind;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		meme = malloc(new_size);
		if (meme == NULL)
			return (NULL);

		return (meme);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	meme = malloc(sizeof(*ptr_copy) * new_size);
	if (meme == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = meme;

	for (ind = 0; ind < old_size && ind < new_size; ind++)
		filler[ind] = *ptr_copy++;

	free(ptr);
	return (meme);
}

/**
 * as_lneptr - Reassigns the lineptr variable for _getline
 * @lineptr: A buffer to store an input string from the user
 * @n: The size of lineptr
 * @buffer: The string to assign to lineptr
 * @b: The size of buffer
 */
void as_lneptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getsline - Reads input from a stream either file or user input
 * @lineptr: A buffer to store the input
 * @n: The size of lineptr
 * @stream: The stream to read from
 * Return: The number of bytes read
 */
ssize_t _getsline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t rt;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	as_lneptr(lineptr, n, buffer, input);

	rt = input;
	if (r != 0)
		input = 0;
	return (rt);
}
