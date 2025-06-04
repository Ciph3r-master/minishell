/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-04 17:08:53 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-04 17:08:53 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		exit (EXIT_FAILURE);

	cmd_node->cmd = malloc(sizeof(t_cmd));
	if (!cmd_node)
	{
		free(cmd_node);
		exit (EXIT_FAILURE);
	}
	cmd_node->cmd->args = malloc(sizeof(char *) * 2);

	cmd_node->cmd->cmd = "ls";
	cmd_node->cmd->args[0] = "ls";
	cmd_node->cmd->args[1] = NULL;
	cmd_node->cmd->path = "/usr/bin/ls";

	cmd_node->type = REDIRECT_IN | REDIRECT_OUT | EXTERN;
	cmd_node->fd_in = -1;
	cmd_node->fd_out = -1;
	cmd_node->error_code = 0;
	cmd_node->filename_in = NULL;
	cmd_node->filename_out = "test.txt";
	cmd_node->prev = NULL;
	cmd_node->next = NULL;
	return (cmd_node);
}

//prend une commande et vas effectuer les redirection
//in, out, append,.
int	exec(t_cmd_node *cmd_node, char **env)
{
	if ()
}

int	main(int argc, char **argv, char **env)
{
	t_cmd_node	*cmd_node;
	int			return_code;

	cmd_node = init_cmd_node();
	exec(cmd_node, env);
	printf("return_code:%d\n", return_code);
	return (0);
}
