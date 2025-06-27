/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/27 20:15:07 by thibaud          ###   ########.fr       */
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
	return (1);
}

int	exec_simple_cmd_builtins(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node)
		free_and_exit(data, 1);
	exec_redirections(cmd_node, data);
	if (data->exit_status != 0)
		return (0);
	exec_builtins(cmd_node, data);
	reset_stdin_stdout(data);
	return (1);
}
