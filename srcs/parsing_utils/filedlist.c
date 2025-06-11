#include "minishell.h"
#include <stdlib.h>

static char	*get_filetype_name(t_filetype type)
{
	if (type == FILE_IN)
		return "\e[1;94mIN\e[0m";
	if (type == FILE_OUT)
		return "\e[1;92mOUT\e[0m";
	if (type == FILE_HD)
		return "\e[1;94mHEREDOC\e[0m";
	if (type == FILE_APPEND)
		return "\e[1;92mAPPEND\e[0m";
	return "UNKNOWN";
}

t_filelist	*filelist_create_node(void	*content, t_filetype type)
{
	t_filelist	*node;

	node = malloc(sizeof(t_filelist));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->filename = content;
	node->limiter = NULL;
	node->type = type;
	return (node);
}

t_filelist	*filelist_push_front(t_filelist **filelist, void *content, t_filetype type)
{
	t_filelist *tmp;
	t_filelist	*new_node;

	if (!filelist)
		return (NULL);
	new_node = filelist_create_node(content, type);
	if (!new_node)
		return (NULL);
	if (!*filelist)
	{
		*filelist = new_node;
		return (new_node);
	}
	tmp = *filelist;
	*filelist = new_node;
	tmp->prev = new_node;
	new_node->next = tmp;
	return (*filelist);
}

t_filelist	*filelist_push_back(t_filelist **filelist, void *content, t_filetype type)
{
	t_filelist	*new_node;
	t_filelist	*current;

	if (!filelist)
		return (NULL);
	new_node = filelist_create_node(content, type);
	if (!new_node)
		return (NULL);
	if (*filelist == NULL)
	{
		*filelist = new_node;
		return (new_node);
	}
	current = *filelist;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
	return (*filelist);
}

t_filelist	*filelist_getlast(t_filelist *filelist)
{
	t_filelist	*current;

	current = filelist;
	while (current->next)
		current = current->next;
	return (current);
}

void	print_filelist(t_filelist *filelist, bool reverse)
{
	t_filelist	*current;
	
	current = filelist;
	if (!reverse)
	{
		while (current)
		{
			printf("[%s] {%s} [%s] -> ", current->filename, current->limiter, get_filetype_name(current->type));
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
		printf("[%s] {%s} [%s] -> ", current->filename, current->limiter, get_filetype_name(current->type));
		current = current->prev;
	}
	printf("\n");
}