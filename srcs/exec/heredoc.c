/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/10 01:51:49 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

int	run_heredoc(t_filelist *cur_file_in, t_data *data)
{
	if (!cur_file_in)
		free_and_exit(data, 1);
	cur_file_in->fd = create_tmp_file(cur_file_in, data);
	read_heredoc_fd(cur_file_in, data);
	return (1);
}

int	run_heredoc_in_file_in(t_filelist *file_in, t_data *data)
{
	t_filelist	*cur_file_in;

	if (!file_in)
		free_and_exit(data, 1);
	cur_file_in = file_in;
	while (cur_file_in)
	{
		if (cur_file_in->type == FILE_HD && data->exec_heredoc == 1)
			run_heredoc(cur_file_in, data);
		cur_file_in = cur_file_in->next;
	}
	return (1);
}

int	create_heredoc(t_cmd_node *cmd_node, t_data *data)
{
	t_cmd_node	*cur_cmd;

	if (!cmd_node)
		free_and_exit(data, 1);
	cur_cmd = cmd_node;
	while (cur_cmd)
	{
		if ((cur_cmd->type & HEREDOC) && (data->exec_heredoc == 1))
			run_heredoc_in_file_in(cur_cmd->file_in, data);
		cur_cmd = cur_cmd->next;
	}
	return (1);
}
