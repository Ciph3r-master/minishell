/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_and_hd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:27:53 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/27 21:06:43 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	exec_redir_in(t_filelist *cur_file_in, t_data *data)
{
	char	*filename;

	if (!cur_file_in || !cur_file_in->filename)
		free_and_exit(data, 1);
	filename = cur_file_in->filename;
	if (access(filename, R_OK) == -1)
	{
		redir_in_message(filename, errno);
		data->exit_status = 1;
		return (0);
	}
	cur_file_in->fd = open(filename, O_RDONLY);
	if (cur_file_in->fd == -1)
		free_and_exit(data, 1);
	if (dup2(cur_file_in->fd, STDIN_FILENO) == -1)
	{
		close(cur_file_in->fd);
		cur_file_in->fd = -1;
		free_and_exit(data, 1);
	}
	close(cur_file_in->fd);
	cur_file_in->fd = -1;
	return (1);
}

int	exec_redir_in_hd(t_filelist *cur_file_in, t_data *data)
{
	if (!cur_file_in || !cur_file_in->pathname)
		free_and_exit(data, 1);
	cur_file_in->fd = open(cur_file_in->pathname, O_RDONLY);
	if (cur_file_in->fd == -1)
		free_and_exit(data, 1);
	if (dup2(cur_file_in->fd, STDIN_FILENO) == -1)
	{
		close(cur_file_in->fd);
		cur_file_in->fd = -1;
		free_and_exit(data, 1);
	}
	close(cur_file_in->fd);
	cur_file_in->fd = -1;
	return (1);
}

int	exec_redir_in_and_hd(t_filelist	*file_in, t_data *data)
{
	t_filelist	*cur_file_in;

	if (!file_in)
		free_and_exit(data, 1);
	cur_file_in = file_in;
	while (cur_file_in && data->exit_status == 0)
	{
		if (FILE_IN == cur_file_in->type)
			exec_redir_in(cur_file_in, data);
		else if (FILE_HD == cur_file_in->type)
			exec_redir_in_hd(cur_file_in, data);
		cur_file_in = cur_file_in->next;
	}
	return (1);
}
