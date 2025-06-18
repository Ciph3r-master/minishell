#include "minishell.h"
#include <stdlib.h>


void free_filelist(t_filelist **fl)
{
	t_filelist *current;
	t_filelist *tmp;

	if (!fl || !*fl)
		return;
	current = *fl;
	while (current)
	{
		tmp = current->next;
		if (current->filename)
			free(current->filename);
		if (current->limiter)
			free(current->limiter);
		free(current);
		current = tmp;
	}
	*fl = NULL;
}

void free_cmd(t_cmd **cmd)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->pathname)
		free((*cmd)->pathname);
	if ((*cmd)->cmd)
		free((*cmd)->cmd);
	if ((*cmd)->args)
	{
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			i++;
		}
		free((*cmd)->args);
	}
	free(*cmd);
	*cmd = NULL;
}
void free_cmd_list(t_cmd_node **cmd_node)
{
	t_cmd_node *current;
	t_cmd_node *tmp;

	if (!cmd_node || !*cmd_node)
		return;
	current = *cmd_node;
	while (current)
	{
		tmp = current->next;
		if (current->file_in)
			free_filelist(&current->file_in);
		if (current->file_out)
			free_filelist(&current->file_out);
		if (current->cmd)
			free_cmd(&current->cmd);
		free(current);
		current = tmp;
	}
	*cmd_node = NULL;
}
