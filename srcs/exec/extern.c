/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:28:27 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 02:53:02 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

int	get_child_exit_status(t_data *data)
{
	int		status;
	int		sig;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		data->exit_status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	signal(SIGINT, sigint_handler);
	return (1);
}

int	execute_cmd_in_child_process(t_cmd_node *cmd_node, t_data *data)
{
	int		pid;
	char	*pathname;
	char	**args;

	pathname = cmd_node->cmd->pathname;
	args = cmd_node->cmd->args;
	pid = fork();
	if (-1 == pid)
		free_and_exit(data, 1);
	if (0 == pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close_saved_fds(data);
		if (execve(pathname, args, data->env_copy) == -1)
			free_and_exit(data, 1);
	}
	else
		get_child_exit_status(data);
	return (1);
}

int	exec_extern(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	is_cmd_name_executable(cmd_node, data);
	if (cmd_node->cmd->pathname == NULL)
		get_cmd_path_name(cmd_node, data);
	if (cmd_node->cmd->pathname != NULL)
		execute_cmd_in_child_process(cmd_node, data);
	return (1);
}

int	exec_simple_cmd_extern(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node)
		free_and_exit(data, 1);
	exec_redirections(cmd_node, data);
	if (data->exit_status != 0)
	{
		reset_stdin_stdout(data);
		return (0);
	}
	cmd_is_directory(cmd_node, data);
	exec_extern(cmd_node, data);
	reset_stdin_stdout(data);
	return (1);
}
