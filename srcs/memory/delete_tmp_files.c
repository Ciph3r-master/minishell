/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tmp_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:55:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/07/19 03:13:52 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	delete_tmps(t_filelist *cur_file_in)
{
	while (cur_file_in)
	{
		if (cur_file_in->type == FILE_HD)
		{
			if (cur_file_in->fd != -1)
			{
				close(cur_file_in->fd);
				cur_file_in->fd = -1;
			}
			if (cur_file_in->pathname)
			{
				unlink(cur_file_in->pathname);
				free(cur_file_in->pathname);
				cur_file_in->pathname = NULL;
			}
		}
		cur_file_in = cur_file_in->next;
	}
}

void	delete_tmp_files(t_data *data)
{
	t_cmd_node	*cur_cmd;

	if (!data || !data->cmd_node)
		return ;
	cur_cmd = data->cmd_node;
	while (cur_cmd)
	{
		delete_tmps(cur_cmd->file_in);
		cur_cmd = cur_cmd->next;
	}
}
