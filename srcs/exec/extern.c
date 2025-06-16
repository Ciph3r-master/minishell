/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:47:00 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/16 19:01:39 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int exec_extern(t_cmd_node *cmd_node)
{

	return (1);
}

int exec_simple_cmd_extern(t_cmd_node *cmd_node)
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
	if (exec_extern(cmd_node) != 1)
		return (-1);
	if (reset_stdin_stdout(saved_stdin, saved_stdout) != 1)
		return (-1);
	return (1);
}
