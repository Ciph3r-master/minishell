/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-03 16:49:42 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-03 16:49:42 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd_node;
	t_cmd		cmd;

	cmd.cmd = "cat";
	cmd.args[0] = "cat";
	cmd.path = "usr/bin/cat";

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		exit (EXIT_FAILURE);
	cmd_node->type = EXTERN;
	cmd_node->fd_in = -1;
	cmd_node->fd_out = -1;
	cmd_node->error_code = 0;
	cmd_node->filename_in = "test.txt";
	cmd_node->filename_out = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;
	return (cmd_node);
}

int	redirect_in(void)
{
	int		fd_in;
	char	*filename;

	fd_in = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == dup2(fd_in, STDOUT_FILENO))
	{
		perror("dup2:");
		return (1);
	}
	return (0);
}

// check les valeurs initialise dans la
// structure et execute en fonction
//
int	exec(t_cmd_node *cmd_node, char **env)
{
	if (cmd_node->filename_in)
		redirect_in();
	exec_cmd();
	if (cmd_node->filename_in)
		close(cmd_node->fd_in);
}

// le main remplace la partie parsing
// et envoi a la fonction exec, une structure ou
// une liste chaine de structure, qui vas etre execute
int	main(int argc, char **argv, char **env)
{
	t_cmd_node	*cmd_node;
	int			return_code;

	cmd_node = init_cmd_node();
	printf("filename_in:%s\n", cmd_node->filename_in);
	printf("filename_in:%s\n", cmd_node->cmd.cmd);
	printf("filename_in:%s\n", cmd_node->cmd.args[0]);
	printf("filename_in:%s\n", cmd_node->cmd.path);

	return_code = exec(cmd_node, env);
	printf("return_code :%s\n", return_code);
	return (0);
}
