/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:39:46 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 02:51:00 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
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

void	exec_pipe_child(t_cmd_node *cur_cmd, t_data *data, int *pids)
{
	free(pids);
	if (data->old_pipe[0] != -1)
	{
		dup2(data->old_pipe[0], STDIN_FILENO);
		close(data->old_pipe[0]);
	}
	if (cur_cmd->next)
	{
		dup2(data->new_pipe[1], STDOUT_FILENO);
		close(data->new_pipe[0]);
		close(data->new_pipe[1]);
	}
	if (data->old_pipe[1] != -1)
		close(data->old_pipe[1]);
	exec_simple_cmd(cur_cmd, data);
	free_and_exit(data, data->exit_status);
}

int	exec_pipe_loop_cmd(t_data *data, t_cmd_node *cur_cmd, int *pids, int *i)
{
	pid_t		pid;

	if (cur_cmd->next)
		if (pipe(data->new_pipe) == -1)
			free_and_exit(data, 1);
	pid = fork();
	if (pid == -1)
		free_and_exit(data, 1);
	if (pid == 0)
		exec_pipe_child(cur_cmd, data, pids);
	pids[(*i)++] = pid;
	if (data->old_pipe[0] != -1)
		close(data->old_pipe[0]);
	if (data->old_pipe[1] != -1)
		close(data->old_pipe[1]);
	data->old_pipe[0] = data->new_pipe[0];
	data->old_pipe[1] = data->new_pipe[1];
	return (1);
}

// void	exec_pipe_get_exit_status(t_data *data, pid_t *pids, int i)
// {
// 	int	status;
// 	int	j;

// 	j = 0;
// 	data->exit_status = 0;
// 	while (j < i)
// 	{
// 		waitpid(pids[j], &status, 0);
// 		if (WIFEXITED(status) && j == i - 1)
// 			data->exit_status = WEXITSTATUS(status);
// 		j++;
// 	}
// }

	#include <stdio.h>

void	exec_pipe_get_exit_status(t_data *data, pid_t *pids, int i)
{
	int	status;
	int	j;
	int	sig;

	j = 0;
	data->exit_status = 0;
	signal(SIGINT, SIG_IGN);
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			data->exit_status = 128 + sig;
			if (sig == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
			else if (sig == SIGQUIT)
				write(STDERR_FILENO, "Quit minishell(core dumped)\n", 28);
		}
		if (WIFEXITED(status) && j == i - 1)
			data->exit_status = WEXITSTATUS(status);
		j++;
	}
	signal(SIGINT, sigint_handler);
}

int	exec_pipe(t_cmd_node *cmd_node, t_data *data)
{
	t_cmd_node	*cur_cmd;
	pid_t		*pids;
	int			i;

	data->old_pipe[0] = -1;
	data->old_pipe[1] = -1;
	cur_cmd = cmd_node;
	i = 0;
	pids = malloc(sizeof(int) * size_pids(cmd_node));
	if (!pids)
		free_and_exit(data, 1);
	while (cur_cmd)
	{
		exec_pipe_loop_cmd(data, cur_cmd, pids, &i);
		cur_cmd = cur_cmd->next;
	}
	exec_pipe_get_exit_status(data, pids, i);
	close_saved_fds(data);
	free(pids);
	return (1);
}
