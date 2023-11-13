#include "shell.h"

/**
 * pl_alias_end - Adds a node to the end of an alias_t linked list.
 * @ahe: A pointer to the head of the alias_t list.
 * @nme: The name of the new alias to be added.
 * @val: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL as return value.
 *         Otherwise - a pointer to the new node in the list.
 */
alias_t *pl_alias_end(alias_t **ahe, char *nme, char *val)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(nme) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = val;
	_strcpy(new_node->name, nme);

	if (*ahe)
	{
		last = *ahe;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*ahe = new_node;

	return (new_node);
}

/**
 * free_alias_list - Frees an alias_t linked list.
 * @ahe: The head of the alias_t list.
 */
void free_alias_list(alias_t *ahe)
{
	alias_t *next;

	while (ahe)
	{
		next = ahe->next;
		free(ahe->name);
		free(ahe->value);
		free(ahe);
		ahe = next;
	}
}

/**
 * pl_node_end - Adds a node to the end of a list_t linked list.
 * @ahe: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *pl_node_end(list_t **ahe, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*ahe)
	{
		last = *ahe;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*ahe = new_node;

	return (new_node);
}

/**
 * free_list - Frees a list_t linked list.
 * @ahe: The head of the list_t list.
 */
void free_list(list_t *ahe)
{
	list_t *next;

	while (ahe)
	{
		next = ahe->next;
		free(ahe->dir);
		free(ahe);
		ahe = next;
	}
}
