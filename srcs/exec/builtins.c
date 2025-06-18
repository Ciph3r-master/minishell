/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/17 22:39:03 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	exec_builtins(t_cmd_node *cmd_node, t_data *data)
{
	char	*cmd;

	(void)data;
	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd->cmd)
		return (-1);
	cmd = cmd_node->cmd->cmd;
	if (ft_strcmp("pwd", cmd) == 0)
		builtin_pwd();
	else
		printf("minishell: %s: command not found\n", cmd);
	return (1);
}

int	exec_simple_cmd_builtins(t_cmd_node *cmd_node, t_data *data)
{
	int	exec_out;
	int	saved_stdin;
	int	saved_stdout;

	if (!cmd_node)
		return (-1);
	if (save_stdin_stdout(&saved_stdin, &saved_stdout) == -1)
		return (-1);
	exec_out = exec_redirections(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	exec_out = cmd_is_directory(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	exec_out = exec_builtins(cmd_node, data);
	if (exec_out != 1)
		return (exec_out);
	if (reset_stdin_stdout(saved_stdin, saved_stdout) != 1)
		return (-1);
	return (1);
}
