/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_and_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:08:37 by thibaud           #+#    #+#             */
/*   Updated: 2025/07/15 18:55:37 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "minishell.h"

int	open_redir_out(t_data *data, t_filelist *cur_file_out, int type)
{
	char	*filename;

	filename = cur_file_out->filename;
	if (type == 1)
		cur_file_out->fd = open(filename, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	if (type == 2)
		cur_file_out->fd = open(cur_file_out->filename, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (cur_file_out->fd == -1)
	{
		if (errno == 0)
			free_and_exit(data, 1);
		else if (errno == EISDIR)
			msg_is_a_directory(data, 1, filename);
		else if (errno == ENOTDIR)
			msg_not_a_directory(data, 1, filename);
		else if (errno == EACCES)
			msg_permission_denied(data, 1, filename);
		else if (errno == ENOENT)
			msg_no_such_file_or_directory(data, 1, filename);
		else
			msg_error(data, 1, filename);
	}
	return (1);
}

int	exec_redir_out(t_filelist *cur_file_out, t_data *data)
{
	if (!cur_file_out || !cur_file_out->filename)
		free_and_exit(data, 1);
	open_redir_out(data, cur_file_out, 1);
	if (cur_file_out->fd == -1)
		return (0);
	if (dup2(cur_file_out->fd, STDOUT_FILENO) == -1)
	{
		close(cur_file_out->fd);
		cur_file_out->fd = -1;
		free_and_exit(data, 1);
	}
	close(cur_file_out->fd);
	cur_file_out->fd = -1;
	return (1);
}

int	exec_redir_append(t_filelist *cur_file_out, t_data *data)
{
	if (!cur_file_out || !cur_file_out->filename)
		free_and_exit(data, 1);
	open_redir_out(data, cur_file_out, 2);
	if (cur_file_out->fd == -1)
		return (0);
	if (dup2(cur_file_out->fd, STDOUT_FILENO) == -1)
	{
		close(cur_file_out->fd);
		cur_file_out->fd = -1;
		free_and_exit(data, 1);
	}
	close(cur_file_out->fd);
	cur_file_out->fd = -1;
	return (1);
}

int	exec_redir_out_and_append(t_filelist *file_out, t_data *data)
{
	t_filelist	*cur_file_out;
	int			exec_redir;

	if (!file_out)
		free_and_exit(data, 1);
	cur_file_out = file_out;
	exec_redir = 1;
	while (cur_file_out && data->exit_status == 0)
	{
		if (cur_file_out->type == FILE_OUT && exec_redir)
			exec_redir = exec_redir_out(cur_file_out, data);
		else if (cur_file_out->type == FILE_APPEND && exec_redir)
			exec_redir = exec_redir_append(cur_file_out, data);
		cur_file_out = cur_file_out->next;
	}
	return (1);
}
