#include "shell.h"

/**
 * get_loc - Locates a command in the PATH
 * @command: The command to locate
 * Return: If an error occurs or the command cannot be loc
 *         Otherwise - the full pathname of the comma
 */
char *get_loc(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_pth_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->drty) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->drty);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->nts;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_pth_dir - Copies path but also replaces leadi
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 * Return: A copy of path with any leading/sandwiched/traili
 *	   with the current working directo
 */
char *fill_pth_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_pth_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list
 * @path: The colon-separated list of directories
 * Return: A pointer to the initialized linked list
 */
list_t *get_pth_dir(char *path)
{
	int ind;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_pth_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (ind = 0; dirs[ind]; ind++)
	{
		if (pl_node_end(&head, dirs[ind]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
