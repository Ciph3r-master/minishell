/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/16 00:38:05 by thibaud          ###   ########.fr       */
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
	return (1);
}

int	reset_stdin_stdout(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (-1);
	return (1);
}

int	exec_redirections(t_cmd_node *cmd_node)
{
	int	node_type;
	int	exec_out;

	node_type = INT_MIN;
	exec_out = 0;
	if (!cmd_node || !cmd_node->type)
		return (-1);
	if (REDIRECT_IN & node_type || HEREDOC & node_type)
	{
		exec_out = exec_redir_in_and_hd(cmd_node->file_in);
		if (-1 == exec_out)
			return (-1);
		if (-2 == exec_out)
			return (-2);
	}
	if (REDIRECT_OUT & node_type || APPEND & node_type)
	{
		exec_out = exec_redir_out_and_append(cmd_node->file_in);
		if (-1 == exec_out)
			return (-1);
	}
	return (1);
}

int	exec_simple_cmd_builtins(t_cmd_node *cmd_node)
{
	int	exec_out;
	int saved_stdin;
	int saved_stdout;

	if (!cmd_node || !cmd_node->type)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	exec_out = exec_redirections(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	if (exec_builtins(cmd_node) != 1)
		return (-1);
	if (reset_stdin_stdout(saved_stdin, saved_stdout) != 1)
		return (-1);
	return (1);
}
