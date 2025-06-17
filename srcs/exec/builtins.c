/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/16 22:15:30 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	exec_builtins(t_cmd_node *cmd_node)
{
	char	*cmd;

	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd->cmd)
		return (-1);
	cmd = cmd_node->cmd->cmd;
	if (ft_strcmp("pwd", cmd))
		builtin_pwd();
	else
		printf("minishell: %s: command not found", cmd);
	return (1);
}

int	exec_simple_cmd_builtins(t_cmd_node *cmd_node)
{
	int	exec_out;
	int	saved_stdin;
	int	saved_stdout;

	if (!cmd_node || !cmd_node->type)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (-1);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(saved_stdin);
		return (-1);
	}
	exec_out = exec_redirections(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	if (exec_builtins(cmd_node) != 1)
		return (-1);
	if (reset_stdin_stdout(saved_stdin, saved_stdout) != 1)
		return (-1);
	return (1);
}
