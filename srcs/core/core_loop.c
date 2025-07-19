/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:51:04 by vscode            #+#    #+#             */
/*   Updated: 2025/07/19 02:26:23 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell.h"

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

void	handle_user_input(t_data *data)
{
	while (1)
	{
		save_stdin_stdout(data);
		g_exit_status = 0;
		data->exec_heredoc = 1;
		data->line = readline("minishell> ");
		if (!data->line)
			exit_minishell(data);
		free_cmd_list(&data->cmd_node);
		free_tokenlist(&data->tokenlist);
		add_history(data->line);
		if (!check_quotes(data->line))
		{
			close_saved_fds(data);
			continue ;
		}
		if (g_exit_status != 0)
			data->exit_status = g_exit_status;
		init_tokens(data);
		data->exit_status = 0;
		free(data->line);
		exec(data);
	}
}
