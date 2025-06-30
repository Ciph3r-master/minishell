/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/27 22:33:11 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data					data;

	(void)argc;
	(void)argv;
	init_signals();
	init_data(&data, env);
	while (1)
	{
		if (save_stdin_stdout(&data.saved_stdin, &data.saved_stdout) == -1)
			free_and_exit(&data, 1);
		data.line = readline("minishell> ");
		if (!data.line)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			free_and_exit(&data, data.exit_status);
		}
		data.exit_status = 0;
		free_cmd_list(&data.cmd_node);
		free_tokenlist(&data.tokenlist);
		add_history(data.line);
		init_tokens(&data);
		free(data.line);
		printf("\n ---------- exec -------\n\n");
		exec(&data);
		printf("exit status:%d\n", data.exit_status);
	}
	return (0);
}
