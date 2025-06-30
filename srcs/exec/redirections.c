/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:24:41 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/27 17:57:11 by thibaud          ###   ########.fr       */
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

int	reset_stdin_stdout(t_data *data)
{
	if (dup2(data->saved_stdin, STDIN_FILENO) == -1)
		free_and_exit(data, 1);
	if (dup2(data->saved_stdout, STDOUT_FILENO) == -1)
		free_and_exit(data, 1);
	close(data->saved_stdin);
	close(data->saved_stdout);
	return (1);
}

int	exec_redirections(t_cmd_node *cmd_node, t_data *data)
{
	int	node_type;

	node_type = cmd_node->type;
	if (!cmd_node || !cmd_node->type)
		free_and_exit(data, 1);
	if (REDIRECT_IN & node_type || HEREDOC & node_type)
		exec_redir_in_and_hd(cmd_node->file_in, data);
	if (REDIRECT_OUT & node_type || APPEND & node_type)
		exec_redir_out_and_append(cmd_node->file_out, data);
	return (1);
}
