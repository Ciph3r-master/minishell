/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/17 23:57:53 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"

sig_atomic_t	g_exit_status = 0;

bool	check_quotes(char *line)
{
	int	i;
	int	dquotes;
	int	quotes;

	dquotes = 0;
	quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			dquotes++;
		if (line[i] == '\'')
			quotes++;
		i++;
	}
	if (dquotes % 2 != 0 || quotes % 2 != 0)
		return (false);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_signals();
	init_data(&data, env);
	while (1)
	{
		save_stdin_stdout(&data);
		g_exit_status = 0;
		data.exec_heredoc = 1;
		data.line = readline("minishell> ");
		if (!data.line)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			free_and_exit(&data, data.exit_status);
		}
		free_cmd_list(&data.cmd_node);
		free_tokenlist(&data.tokenlist);
		add_history(data.line);
		if (!check_quotes(data.line))
		{
			close_saved_fds(&data);
			continue;
		}
		if (g_exit_status != 0)
			data.exit_status = g_exit_status;
		init_tokens(&data);
		data.exit_status = 0;
		free(data.line);
		printf("\n ---------- exec -------\n\n");
		exec(&data);
	}
	return (0);
}
