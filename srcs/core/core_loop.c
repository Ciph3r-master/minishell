/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:51:04 by vscode            #+#    #+#             */
/*   Updated: 2025/07/24 02:42:39 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell.h"
#include "libft.h"

int	valid_minishell(int ac)
{
	if (ac != 1)
	{
		printf("Error: minishell does not take any arguments\n");
		return (0);
	}
	if (!isatty(STDIN_FILENO))
	{
		printf("Error: minishell must be run in an interactive terminal\n");
		return (0);
	}
	if (!isatty(STDOUT_FILENO))
	{
		printf("Error: stdout is not a terminal\n");
		return (0);
	}
	return (1);
}

void	init_minishell(t_data *data, char **env)
{
	init_signals();
	init_data(data, env);
}

static void	exit_minishell(t_data *data)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	free_and_exit(data, data->exit_status);
}

static	int	check_syntax_error(t_data *data)
{
	if (!check_quotes(data->line) || is_only_whitespace(data->line))
	{
		close_saved_fds(data);
		return (1);
	}
	return (0);
}

void	handle_user_input(t_data *data)
{
	while (1)
	{
		save_stdin_stdout(data);
		g_exit_status = 0;
		data->exec_heredoc = 1;
		data->pipe_signal = 0;
		data->line = readline("minishell> ");
		if (g_exit_status != 0)
			data->exit_status = g_exit_status;
		if (!data->line)
			exit_minishell(data);
		free_cmd_list(&data->cmd_node);
		free_tokenlist(&data->tokenlist);
		add_history(data->line);
		if (check_syntax_error(data))
			continue ;
		data->prev_exit_status = data->exit_status;
		init_tokens(data);
		free(data->line);
		data->exit_status = 0;
		exec(data);
		delete_tmp_files(data);
		close_saved_fds(data);
	}
}
