#include "minishell.h"
#include <stdlib.h>

t_cmd_node *cmdlist_create_node(void)
{
	t_cmd_node *node;

	node = malloc(sizeof(t_cmd_node));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->file_in = NULL;
	node->file_out = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->type = 0;
	node->error_code = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cmd_node *cmdlist_push_front(t_cmd_node **cmdlist)
{
	t_cmd_node *tmp;
	t_cmd_node *new_node;

	if (!cmdlist)
		return (NULL);
	new_node = cmdlist_create_node();
	if (!new_node)
		return (NULL);
	if (!*cmdlist)
	{
		*cmdlist = new_node;
		return (new_node);
	}
	tmp = *cmdlist;
	*cmdlist = new_node;
	tmp->prev = new_node;
	new_node->next = tmp;
	return (*cmdlist);
}

t_cmd_node *cmdlist_push_back(t_cmd_node **cmdlist)
{
	t_cmd_node *new_node;
	t_cmd_node *current;

	if (!cmdlist)
		return (NULL);
	new_node = cmdlist_create_node();
	if (!new_node)
		return (NULL);
	if (*cmdlist == NULL)
	{
		*cmdlist = new_node;
		return (new_node);
	}
	current = *cmdlist;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
	return (*cmdlist);
}

t_cmd_node *cmdlist_getlast(t_cmd_node *cmdlist)
{
	t_cmd_node *current;

	if (!cmdlist)
		return (NULL);
	current = cmdlist;
	while (current && current->next)
		current = current->next;
	return (current);
}

void print_cmdlist(t_cmd_node *cmdlist)
{
	t_cmd_node *current;

	current = cmdlist;
	while (current)
	{
		printf("\n\e[1;91mCommand\e[0m : [%s]\n", current->cmd->cmd);
		printf("FD in [%d] FD out [%d]\n", current->fd_in, current->fd_out);
		if (current->file_in)
		{
			printf("REDIRECT in :\n");
			print_filelist(current->file_in, false);
		}
		if (current->file_out)
		{
			printf("REDIRECT out :\n");
			print_filelist(current->file_out, false);
		}
		printf("Arguments :\n");
		int i = 0;
		while (current->cmd->args[i])
		{
			printf("[%s]\n", current->cmd->args[i]);
			i++;
		}
		current = current->next;
	}
}