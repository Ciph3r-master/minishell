/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tmp_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:55:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/13 19:55:51 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

void	delete_tmps(t_filelist *cur_file_in)
{
	while (cur_file_in)
	{
		if (cur_file_in->type == FILE_HD)
		{
			if (cur_file_in->fd != -1)
			{
				if (close(cur_file_in->fd) == -1)
					perror("close");
				cur_file_in->fd = -1;
			}
			if (cur_file_in->pathname)
			{
				printf("unlinking %s\n", cur_file_in->pathname);
				if (unlink(cur_file_in->pathname) == -1)
					perror("unlink");
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
