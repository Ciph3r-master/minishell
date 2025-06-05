#include "minishell.h"
#include <stdlib.h>

static char	*get_tokentype_name(t_tokentype type)
{
	if (type == TARG)
		return "ARG";
	if (type == TBUILTIN)
		return "\e[1;91mBUILTIN\e[0m";
	if (type == TDQUOTES)
		return "DQUOTES";
	if (type == TQUOTES)
		return "QUOTES";
	if (type == TEXTERN)
		return "EXTERN";
	if (type == TWORD)
		return "WORD";
	if (type == TRD_IN)
		return "\e[1;92mREDIRECT IN\e[0m";
	if (type == TRD_OUT)
		return "\e[1;92mREDIRECT OUT\e[0m";
	if (type == TOPERATOR)
		return "\e[1;92mOPERATOR\e[0m";
	if (type == THD)
		return "\e[1;92mHEREDOC\e[0m";
	if (type == TPIPE)
		return "\e[1;92mPIPE\e[0m";
	if (type == TAPPEND)
		return "\e[1;92mAPPEND\e[0m";
	return "UNKNOWN";
}

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
		while (current)
		{
			printf("[%s]-[%s] -> ", current->token, get_tokentype_name(current->type));
			current = current->next;
		}
		printf("\n");
		return ;
	}
	while (current->next)
		current = current->next;
	printf("REVERSE\n");
	while (current)
	{
		printf("%s [%s] -> ", current->token, get_tokentype_name(current->type));
		current = current->prev;
	}
	printf("\n");
}