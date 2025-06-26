/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/27 01:08:14 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	exec_builtins(t_cmd_node *cmd_node, t_data *data)
{
	char	*cmd;

	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd->cmd)
		return (-1);
	cmd = cmd_node->cmd->cmd;
	if (ft_strcmp("pwd", cmd) == 0)
		builtin_pwd();
	else
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		data->exit_status = 1;
	}
	return (1);
}

int	exec_simple_cmd_builtins(t_cmd_node *cmd_node, t_data *data)
{
	int	exec_out;

	if (!cmd_node)
		return (-1);
	exec_out = exec_redirections(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	exec_out = exec_builtins(cmd_node, data);
	if (exec_out != 1)
		return (exec_out);
	if (reset_stdin_stdout(data->saved_stdin, data->saved_stdout) != 1)
		return (-1);
	return (1);
}
