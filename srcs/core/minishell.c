/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/17 23:05:04 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	t_data		data;

	(void)argc;
	(void)argv;
	// init_signals();
	init_data(&data, env);
	while (1)
	{
		free_cmd_list(&data.cmd_node);
		free_tokenlist(&data.tokenlist);
		data.line = readline("minishell> ");
		if (!data.line)
		{
			write(1, "exit\n", 5);
			free_and_exit(&data);
		}
		add_history(data.line);
		init_tokens(&data);
		free(data.line);
	}
	rl_clear_history();
	free_all(&data);
	return (0);
}
