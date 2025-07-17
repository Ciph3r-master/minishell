/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bill <bill@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:32:10 by bill              #+#    #+#             */
/*   Updated: 2025/07/16 22:33:13 by bill             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_filelist(t_filelist **fl)
{
	t_filelist	*current;
	t_filelist	*tmp;

	if (!fl || !*fl)
		return ;
	current = *fl;
	while (current)
	{
		tmp = current->next;
		if (current->filename)
			free(current->filename);
		current->filename = NULL;
		if (current->limiter)
			free(current->limiter);
		if (current->pathname)
			free(current->pathname);
		current->pathname = NULL;
		current->limiter = NULL;
		free(current);
		current = tmp;
	}
	*fl = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->pathname)
		free((*cmd)->pathname);
	(*cmd)->pathname = NULL;
	if ((*cmd)->cmd)
		free((*cmd)->cmd);
	(*cmd)->cmd = NULL;
	if ((*cmd)->args)
	{
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			i++;
		}
		free((*cmd)->args);
	}
	(*cmd)->args = NULL;
	free((*cmd));
	*cmd = NULL;
}

void	free_cmd_list(t_cmd_node **cmd_node)
{
	t_cmd_node	*current;
	t_cmd_node	*tmp;

	if (!cmd_node || !*cmd_node)
		return ;
	current = *cmd_node;
	while (current)
	{
		tmp = current->next;
		free_filelist(&current->file_in);
		free_filelist(&current->file_out);
		free_cmd(&current->cmd);
		free(current);
		current = tmp;
	}
	*cmd_node = NULL;
}
