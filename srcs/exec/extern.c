/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:47:00 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/16 00:51:28 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int exec_simple_cmd_extern(t_cmd_node *cmd_node)
{
	char	*pathname;

	pathname = NULL;
	if (-1 == get_cmd_path_name(cmd_node))
	{
		printf("bash: %s: command not found", cmd_node->cmd->cmd);
		return (-1);
	}
	execute_cmd_in_child_process(pathname, argv, env);
	free(pathname);
	return (0);
}
