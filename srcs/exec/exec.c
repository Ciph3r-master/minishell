/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:58:30 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/18 23:36:53 by thibaud          ###   ########.fr       */
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
	int	exec_out;

	node_type = cmd_node->type;
	if (BUILTIN & node_type)
	{
		exec_out = exec_simple_cmd_builtins(cmd_node, data);
		if (exec_out == -1)
			free_and_exit(data, 326);
		if (exec_out == -2)
			return (-2);
	}
	if (EXTERN & node_type)
	{
		exec_out = exec_simple_cmd_extern(cmd_node, data);
		if (exec_out == -1)
			free_and_exit(data, 326);
		if (exec_out == -2)
			return (-2);
	}
	return (1);
}

int	exec(t_data *data)
{
	t_cmd_node	*cmd_node;
	int			exec_out;

	if (!data || !data->cmd_node)
		return (-2);
	cmd_node = data->cmd_node;
	exec_out = 0;
	if (pipeline_has_heredoc(cmd_node))
	{
		if (-1 == exec_heredoc(cmd_node, data))
			free_and_exit(data, 1);
	}
	if (!cmd_node->next)
	{
		exec_out = exec_simple_cmd(cmd_node, data);
		if (exec_out != 1)
			return (exec_out);
	}
	else if (cmd_node->next)
	{
		if (exec_pipe(cmd_node, data) == -1)
			free_and_exit(data, 1);
	}
	return (0);
}
