/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-18 17:39:46 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-18 17:39:46 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	size_pids(t_cmd_node *cmd_node)
{
	t_cmd_node	*cur_cmd;
	int			size_pids;

	if (!cmd_node)
		return (-1);
	cur_cmd = cmd_node;
	size_pids = 0;
	while (cur_cmd)
	{
		size_pids++;
		cur_cmd = cur_cmd->next;
	}
	return (size_pids);
}

// on va dans une boucle, executer chaque commande suivi d'un pipe
// on va faire les redirection des pipe avant celle
// des redir_in et de redir_out, pour chaque commande
// puis on fait les redir_in et out, ainsi on a les redir qui prennent
// la priorité sur les pipes
int	exec_pipe(t_cmd_node *cmd_node, t_data *data)
{
	int			old_pipe[2];
	int			new_pipe[2];
	pid_t		pid;
	pid_t		*pids;
	int			status;
	int			i;
	t_cmd_node	*cur_cmd;

	old_pipe[0] = -1;
	old_pipe[1] = -1;
	cur_cmd = cmd_node;
	i = 0;
	pids = malloc(sizeof(int) * size_pids(cmd_node));
	if (!pids)
		return (-1);

	while (cur_cmd)
	{
		if (cur_cmd->next)
			pipe(new_pipe);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if (old_pipe[0] != -1)
			{
				dup2(old_pipe[0], STDIN_FILENO);
				close(old_pipe[0]);
			}
			if (cur_cmd->next)
			{
				dup2(new_pipe[1], STDOUT_FILENO);
				close(new_pipe[0]);
				close(new_pipe[1]);
			}
			if (old_pipe[1] != -1)
				close(old_pipe[1]);
			exec_redirections(cmd_node);
			exec_simple_cmd(cmd_node, data);
		}
	}

	free(pids);
}
