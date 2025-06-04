#include "minishell.h"
#include <stdlib.h>

t_tokenlist	*dlist_create_node(void	*content, t_tokentype type)
{
	t_tokenlist	*node;

	node = malloc(sizeof(t_tokenlist));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->token = content;
	node->type = type;
	return (node);
}

t_tokenlist	*dlist_push_front(t_tokenlist **tokenlist, void *content, t_tokentype type)
{
	t_tokenlist *tmp;
	t_tokenlist	*new_node;

	if (!tokenlist)
		return (NULL);
	new_node = dlist_create_node(content, type);
	if (!new_node)
		return (NULL);
	if (!*tokenlist)
	{
		*tokenlist = new_node;
		return (new_node);
	}
	tmp = *tokenlist;
	*tokenlist = new_node;
	tmp->prev = new_node;
	new_node->next = tmp;
	return (*tokenlist);
}

t_tokenlist	*dlist_push_back(t_tokenlist **tokenlist, void *content, t_tokentype type)
{
	t_tokenlist	*new_node;
	t_tokenlist	*current;

	if (!tokenlist)
		return (NULL);
	new_node = dlist_create_node(content, type);
	if (!new_node)
		return (NULL);
	if (*tokenlist == NULL)
	{
		*tokenlist = new_node;
		return (new_node);
	}
	current = *tokenlist;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
	return (*tokenlist);
}

void	print_dlist(t_tokenlist *tokenlist, bool reverse)
{
	t_tokenlist	*current;
	
	current = tokenlist;
	if (!reverse)
	{
		printf("IN CORRECT ORDER\n");
		while (current)
		{
			printf("%s [%u]\n", current->token, current->type);
			current = current->next;
		}
		return ;
	}
	while (current->next)
		current = current->next;
	printf("REVERSE ORDER\n");
	while (current)
	{
		printf("%s [%u]\n", current->token, current->type);
		current = current->prev;
	}
}