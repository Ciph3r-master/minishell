/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:24:41 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/16 18:51:54 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	save_stdin_stdout(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (-1);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		close(*saved_stdin);
		return (-1);
	}
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

	node_type = cmd_node->type;
	exec_out = 0;
	if (!cmd_node || !cmd_node->type)
		return (-1);
	if (REDIRECT_IN & node_type || HEREDOC & node_type)
	{
		exec_out = exec_redir_in_and_hd(cmd_node->file_in);
		if (exec_out != 1)
			return (exec_out);
	}
	if (REDIRECT_OUT & node_type || APPEND & node_type)
	{
		exec_out = exec_redir_out_and_append(cmd_node->file_out);
		if (exec_out == -1)
			return (exec_out);
	}
	return (1);
}
