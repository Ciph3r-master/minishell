/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:28:27 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/27 02:45:35 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

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
		return (-1);
	if (0 == pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (-1 != execve(pathname, args, data->env_copy))
			return (-1);
	}
	else
		get_child_exit_status(data);
	return (1);
}

int	exec_extern(t_cmd_node *cmd_node, t_data *data)
{
	char	*cmd;
	char	*pathname;
	int 	exec_out;

	if (!cmd_node || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	cmd = cmd_node->cmd->cmd;
	pathname = cmd_node->cmd->pathname;
	is_cmd_name_executable(cmd_node, data);
	if (pathname == NULL)
	{
		exec_out = get_cmd_path_name(cmd_node, data);
		if (exec_out == -2)
		{
			write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": command not found\n", 20);
			data->exit_status = 127;
			return (exec_out);
		}
	}
	exec_out = execute_cmd_in_child_process(cmd_node, data);
	return (exec_out);
}

int	exec_simple_cmd_extern(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node)
		free_and_exit(data, 1);
	exec_redirections(cmd_node, data);
	cmd_is_directory(cmd_node, data);
	exec_extern(cmd_node, data);
	reset_stdin_stdout(data);
	return (1);
}
