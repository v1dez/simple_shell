#include "shell.h"

/**
 * locate_command - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL (No return value).
 *         Otherwise - the full pathname of the command is returned.
 */
char *fill_pth_dir(char *pth);
{
	char **path_directories, *temp_path;
	list_t *directories_list, *head;
	struct stat st;

	path_directories = _getenv("PATH");
	if (!path_directories || !(*path_directories))
		return (NULL);

	directories_list = parse_path_directories(*path_directories + 5);
	head = directories_list;

	while (directories_list)
	{
		temp_path = malloc(_strlen(directories_list->dir) + _strlen(command) + 2);
		if (!temp_path)
			return (NULL);

		_strcpy(temp_path, directories_list->dir);
		_strcat(temp_path, "/");
		_strcat(temp_path, command);

		if (stat(temp_path, &st) == 0)
		{
			free_list(head);
			return (temp_path);
		}

		directories_list = directories_list->next;
		free(temp_path);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_with_cwd - Copies path but also replaces leading/sandwiched/trailing
 *                      colons (:) with the current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *         with the current working directory.
 */
list_t *get_pth_dir(char *pth);
{
	int j, length = 0;
	char *path_copy, *current_working_dir;

	current_working_dir = *(_getenv("PWD")) + 4;
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (path[j + 1] == ':' || j == 0 || path[j + 1] == '\0')
				length += _strlen(current_working_dir) + 1;
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
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (j == 0)
			{
				_strcat(path_copy, current_working_dir);
				_strcat(path_copy, ":");
			}
			else if (path[j + 1] == ':' || path[j + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, current_working_dir);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[j], 1);
		}
	}
	return (path_copy);
}

/**
 * parse_path_directories - Tokenizes a colon-separated list of
 *                         directories into a list_t linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
char *get_loc(char *command);
{
	int index;
	char **directories, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_with_cwd(path);
	if (!path_copy)
		return (NULL);
	directories = _strtok(path_copy, ":");
	free(path_copy);
	if (!directories)
		return (NULL);

	for (index = 0; directories[index]; index++)
	{
		if (add_node_end(&head, directories[index]) == NULL)
		{
			free_list(head);
			free(directories);
			return (NULL);
		}
	}

	free(directories);

	return (head);
}
