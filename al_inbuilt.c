#include "shell.h"


/**
 * shs_alias - prints all aliases, specific
 * aliases, or sets an alias
 * @args: An array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 * Return: If an error occurs - -1
 * Otherwise - 0
 */

int shs_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int l, rt = 0;
	char *val;

	if (!args[0])
	{
		while (temp)
		{
			writ_alias(temp);
			temp = temp->nts;
		}
		return (rt);
	}
	for (l = 0; args[l]; l++)
	{
		temp = aliases;
		val = _strchr(args[l], '=');
		if (!val)
		{
			while (temp)
			{
				if (_strcmp(args[l], temp->name) == 0)
				{
					writ_alias(temp);
					break;
				}
				temp = temp->nts;
			}
			if (!temp)
				rt = create_err(args + l, 1);/**creaate*/
		}
		else
			def_alias(args[l], val);
	}
	return (rt);
}

/**
 * def_alias - either set an existing alias 'name' with a new value
 * 'value' or creates a new alias with 'name' and 'value'
 * @var_name: Name of alias
 * @val: Value of the alias. First character is a '='.
 */
void def_alias(char *var_name, char *val)
{
	alias_t *temp = aliases;
	int len;
	int j;
	int k;
	char *new_val;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
		return;
	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')/** val*/
			new_val[k++] = val[j];
	}
	new_val[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->val);
			temp->val = new_val;
			break;
		}
		temp = temp->nts;
	}
	if (!temp)
		pl_alias_end(&aliases, var_name, new_val);
}

/**
 * writ_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void writ_alias(alias_t *alias)
{
	char *alias_str;
	int len = _strlen(alias->name) + _strlen(alias->val) + 4;

	alias_str = malloc(sizeof(char) * (len + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->val);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, len);
	free(alias_str);
}
/**
 * repl_alias - Goes through the arguments and replace any matching alias
 * with their value
 * @args: 2D pointer to the arguments
 * @front: adqw SDWEM
 * Return: 2D pointer to the arguments
 */
char **repl_alias(char **args)
{
	alias_t *temp;
	int l;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (l = 0; args[l]; l++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[l], temp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(temp->val) + 1));
				if (!new_val)
				{
					fr_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, temp->val);
				free(args[l]);
				args[l] = new_val;
				l--;
				break;
			}
			temp = temp->nts;
		}
	}

	return (args);
}
