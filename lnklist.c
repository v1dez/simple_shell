#include "shell.h"

/**
 * pl_alias_end - Adds a node to the end of a alinked list.
 * @ahe: A pointer to the head of the list_t list
 * @name: The name of the new alias to be added.
 * @val: The value of the new alias to be added.
 * Return: If an error occurs - NULL as return value.
 *         Otherwise - a pointer to the new node in the list.
 */
alias_t *pl_alias_end(alias_t **ahe, char *name, char *val)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->nts = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->val = val;
	_strcpy(new_node->name, name);

	if (*ahe)
	{
		last = *ahe;
		while (last->nts != NULL)
			last = last->nts;
		last->nts = new_node;
	}
	else
		*ahe = new_node;

	return (new_node);
}

/**
 * pl_node_end - Adds a node to the end of a list_t linked list.
 * @ahe: A pointer to the head of the list_t list in the linked
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

	new_node->drty = dir;
	new_node->nts = NULL;

	if (*ahe)
	{
		last = *ahe;
		while (last->nts != NULL)
			last = last->nts;
		last->nts = new_node;
	}
	else
		*ahe = new_node;

	return (new_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @ahe: THe head of the alias_t list.
 */
void free_alias_list(alias_t *ahe)
{
	alias_t *nts;

	while (ahe)
	{
		nts = ahe->nts;
		free(ahe->name);
		free(ahe->val);
		free(ahe);
		ahe = nts;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @ahe: The head of the list_t list.
 */
void free_list(list_t *ahe)
{
	list_t *nts;

	while (ahe)
	{
		nts = ahe->nts;
		free(ahe->drty);
		free(ahe);
		ahe = nts;
	}
}
