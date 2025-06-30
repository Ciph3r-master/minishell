/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:58:30 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/27 21:06:53 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline_has_heredoc(t_cmd_node *cmd_node)
{
	t_cmd_node	*cur_cmd_node;
	int			node_type;

	cur_cmd_node = cmd_node;
	node_type = cmd_node->type;
	while (cur_cmd_node)
	{
		if (HEREDOC & node_type)
			return (1);
		cur_cmd_node = cur_cmd_node->next;
	}
	return (0);
}

int	exec_simple_cmd(t_cmd_node *cmd_node, t_data *data)
{
	int	node_type;

	node_type = cmd_node->type;
	if (BUILTIN & node_type)
		exec_simple_cmd_builtins(cmd_node, data);
	else if (EXTERN & node_type)
		exec_simple_cmd_extern(cmd_node, data);
	else if (REDIRECT_IN & node_type || HEREDOC & node_type
		|| REDIRECT_OUT & node_type || APPEND & node_type)
	{
		exec_redirections(cmd_node, data);
		reset_stdin_stdout(data);
	}
	return (1);
}

int	exec(t_data *data)
{
	t_cmd_node	*cmd_node;

	if (!data || !data->cmd_node)
		return (1);
	cmd_node = data->cmd_node;
	if (pipeline_has_heredoc(cmd_node))
		exec_heredoc(cmd_node, data);
	if (!cmd_node->next)
		exec_simple_cmd(cmd_node, data);
	else if (cmd_node->next)
		exec_pipe(cmd_node, data);
	return (0);
}
