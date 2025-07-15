/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 01:45:48 by vscode            #+#    #+#             */
/*   Updated: 2025/07/15 21:17:32 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "libft.h"

int	readline_heredoc(t_data *data, char *limiter, int fd)
{
	char	*here_line;

	(void)data;
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

void	child_heredoc_fd(t_data *data, char *limiter, int fd)
{
	signal(SIGINT, heredoc_handler);
	while (readline_heredoc(data, limiter, fd))
		;
	if (close(fd) == -1)
		free_and_exit(data, 1);
	if (g_exit_status == 130)
		free_and_exit(data, 130);
	free_and_exit(data, -1);
}

void	parent_heredoc_fd(t_data *data, pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		data->exec_heredoc = 0;
		data->exit_status = 130;
		close_saved_fds(data);
		write(STDOUT_FILENO, "\n", 1);
	}
	signal(SIGINT, sigint_handler);
}

int	read_heredoc_fd(t_filelist *cur_file_in, t_data *data)
{
	char		*limiter;
	int			fd;
	pid_t		pid;
	int			status;

	status = 0;
	if (!cur_file_in || !cur_file_in->limiter)
		free_and_exit(data, 1);
	limiter = cur_file_in->limiter;
	fd = cur_file_in->fd;
	pid = fork();
	if (pid < 0)
		free_and_exit(data, 1);
	if (pid == 0)
		child_heredoc_fd(data, limiter, fd);
	else
	{
		parent_heredoc_fd(data, pid, status);
		if (close(fd) == -1)
			free_and_exit(data, 1);
		cur_file_in->fd = -1;
	}
	return (1);
}
