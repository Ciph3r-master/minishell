/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/08 04:58:34 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	exec_builtins(t_cmd_node *cmd_node, t_data *data)
{
	char	*cmd;

	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	cmd = cmd_node->cmd->cmd;
	if (ft_strcmp("pwd", cmd) == 0)
		builtin_pwd();
	if (ft_strcmp("echo", cmd) == 0)
		builtin_echo(cmd_node);
	if (ft_strcmp("env", cmd) == 0)
		builtin_env(data);
	if (ft_strcmp("unset", cmd) == 0)
		builtin_unset(data, cmd_node);
	if (ft_strcmp("exit", cmd) == 0)
		builtin_exit(data, cmd_node);
	return (1);
}

int	exec_simple_cmd_builtins(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node)
		free_and_exit(data, 1);
	exec_redirections(cmd_node, data);
	if (data->exit_status != 0)
	{
		reset_stdin_stdout(data);
		return (0);
	}
	exec_builtins(cmd_node, data);
	reset_stdin_stdout(data);
	return (1);
}
