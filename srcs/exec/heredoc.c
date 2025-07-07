/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/08 00:15:35 by thibaud          ###   ########.fr       */
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

int	readline_heredoc(char *limiter, int fd)
{
	char	*here_line;

	here_line = readline("> ");
	if (g_exit_status == 130)
		return (0);
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

int	read_heredoc_fd(t_filelist *cur_file_in, t_data *data)
{
	char		*limiter;
	int			fd;
	pid_t		pid;
	int			status;

	if (!cur_file_in || !cur_file_in->limiter)
		free_and_exit(data, 1);
	limiter = cur_file_in->limiter;
	fd = cur_file_in->fd;
	pid = fork();
	if (pid < 0)
		free_and_exit(data, 1);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		while (data->exec_heredoc && readline_heredoc(limiter, fd))
			;
		close(fd);
		if (g_exit_status == 130)
		{
			g_exit_status = 0;
			data->exec_heredoc = 0;
			free_and_exit(data, 130);
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			data->exec_heredoc = 0;
			data->exit_status = 130;
			write(STDOUT_FILENO, "\n", 1);
		}
		signal(SIGINT, sigint_handler);
		if (close(fd) == -1)
			free_and_exit(data, 1);
		cur_file_in->fd = -1;
	}
	return (1);
}

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
		if (cur_file_in->type == FILE_HD)
			run_heredoc(cur_file_in, data);
		cur_file_in = cur_file_in->next;
	}
	return (1);
}

int	exec_heredoc(t_cmd_node *cmd_node, t_data *data)
{
	t_cmd_node	*cur_cmd;

	if (!cmd_node)
		free_and_exit(data, 1);
	cur_cmd = cmd_node;
	while (cur_cmd)
	{
		if (cur_cmd->type & HEREDOC)
			run_heredoc_in_file_in(cur_cmd->file_in, data);
		cur_cmd = cur_cmd->next;
	}
	return (1);
}
