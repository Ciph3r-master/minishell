/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_and_hd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:27:53 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/16 18:47:38 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	exec_redir_in(t_filelist *cur_file_in)
{
	if (!cur_file_in || !cur_file_in->filename)
		return (-1);
	if (access(cur_file_in->filename, F_OK) == -1)
	{
		printf("minishell: %s: ", cur_file_in->filename);
		printf("No such file or directory\n");
		return (-2);
	}
	cur_file_in->fd = open(cur_file_in->filename, O_RDONLY);
	if (cur_file_in->fd == -1)
		return (-1);
	if (dup2(cur_file_in->fd, STDIN_FILENO) == -1)
	{
		close(cur_file_in->fd);
		return (-1);
	}
	close(cur_file_in->fd);
	return (1);
}

int	exec_redir_in_hd(t_filelist *cur_file_in)
{
	if (!cur_file_in || !cur_file_in->pathname)
		return (-1);
	cur_file_in->fd = open(cur_file_in->pathname, O_RDONLY);
	if (cur_file_in->fd == -1)
		return (-1);
	if (dup2(cur_file_in->fd, STDIN_FILENO) == -1)
	{
		close(cur_file_in->fd);
		return (-1);
	}
	close(cur_file_in->fd);
	return (1);
}

int	exec_redir_in_and_hd(t_filelist	*file_in)
{
	t_filelist	*cur_file_in;
	int			exec_out;

	if (!file_in)
		return (-1);
	cur_file_in = file_in;
	while (cur_file_in)
	{
		if (!cur_file_in || !cur_file_in->type)
			return (-1);
		if (FILE_IN == cur_file_in->type)
		{
			exec_out = exec_redir_in(cur_file_in);
			if (exec_out != 1)
				return (exec_out);
		}
		else if (FILE_HD == cur_file_in->type)
		{
			exec_out = exec_redir_in_hd(cur_file_in);
			if (exec_out != 1)
				return (exec_out);
		}
		cur_file_in = cur_file_in->next;
	}
	return (1);
}
