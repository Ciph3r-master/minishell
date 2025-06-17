/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_and_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:08:37 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/16 18:49:09 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

int	exec_redir_out(t_filelist *cur_file_in)
{
	if (!cur_file_in || !cur_file_in->filename)
		return (-1);
	cur_file_in->fd = open(cur_file_in->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cur_file_in->fd == -1)
		return (-1);
	if (dup2(cur_file_in->fd, STDOUT_FILENO) == -1)
	{
		close(cur_file_in->fd);
		cur_file_in->fd = -1;
		return (-1);
	}
	close(cur_file_in->fd);
	cur_file_in->fd = -1;
	return (1);
}

int	exec_redir_append(t_filelist *cur_file_in)
{
	if (!cur_file_in || !cur_file_in->filename)
		return (-1);
	cur_file_in->fd = open(cur_file_in->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cur_file_in->fd == -1)
		return (-1);
	if (dup2(cur_file_in->fd, STDOUT_FILENO) == -1)
	{
		close(cur_file_in->fd);
		cur_file_in->fd = -1;
		return (-1);
	}
	close(cur_file_in->fd);
	cur_file_in->fd = -1;
	return (1);
}

int	exec_redir_out_and_append(t_filelist *file_in)
{
	t_filelist	*cur_file_in;
	int			exec_out;

	if (!file_in)
		return (-1);
	cur_file_in = file_in;
	while (cur_file_in)
	{
		if (!cur_file_in->type)
			return (-1);
		if (FILE_OUT == cur_file_in->type)
		{
			exec_out = exec_redir_out(cur_file_in);
			if (exec_out == -1)
				return (exec_out);
		}
		if (FILE_APPEND == cur_file_in->type)
		{
			exec_out = exec_redir_append(cur_file_in);
			if (exec_out == -1)
				return (exec_out);
		}
		cur_file_in = cur_file_in->next;
	}
	return (1);
}
