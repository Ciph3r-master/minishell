/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/17 01:58:34 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"
#include "libft.h"

int	readline_heredoc(char *limiter, int fd)
{
	char	*here_line;

	here_line = readline("> ");
	if (!here_line)
	{
		write(STDERR_FILENO, "bash: warning: here-document ", 29);
		write(STDERR_FILENO, "delimited by end-of-file (wanted `", 34);
		write(STDERR_FILENO, limiter, ft_strlen(limiter));
		write(STDERR_FILENO, "')\n", 3);
		return (0);
	}
	if (ft_strcmp(limiter, here_line) == 0)
	{
		free(here_line);
		return (0);
	}
	write(fd, here_line, ft_strlen(here_line));
	write(fd, "\n", 1);
	free(here_line);
	return (1);
}

int	read_heredoc_fd(t_filelist *cur_file_in)
{
	char	*limiter;
	int		reading;
	int		fd;

	if (!cur_file_in || !cur_file_in->limiter)
		return (-1);
	limiter = cur_file_in->limiter;
	fd = cur_file_in->fd;
	reading = 1;
	signal(SIGINT, sigint_handler_heredoc);
	while (reading)
		reading = readline_heredoc(limiter, fd);
	signal(SIGINT, sigint_handler);
	if (close(fd) == -1)
		return (-1);
	cur_file_in->fd = -1;
	return (1);
}

int	run_heredoc(t_filelist *cur_file_in)
{
	if (!cur_file_in)
		return (-1);
	cur_file_in->fd = create_tmp_file(cur_file_in);
	if (cur_file_in->fd == -1)
		return (-1);
	if (read_heredoc_fd(cur_file_in) == -1)
		return (-1);
	return (1);
}

int	run_heredoc_in_file_in(t_filelist *file_in)
{
	t_filelist	*cur_file_in;

	if (!file_in)
		return (-1);
	cur_file_in = file_in;
	while (cur_file_in)
	{
		if (cur_file_in->type == FILE_HD)
		{
			if (run_heredoc(cur_file_in) == -1)
				return (-1);
		}
		cur_file_in = cur_file_in->next;
	}
	return (1);
}

int	exec_heredoc(t_cmd_node *cmd_node)
{
	t_cmd_node	*cur_cmd;

	if (!cmd_node)
		return (-1);
	cur_cmd = cmd_node;
	while (cur_cmd)
	{
		if (-1 == run_heredoc_in_file_in(cur_cmd->file_in))
			return (-1);
		cur_cmd = cur_cmd->next;
	}
	return (1);
}
