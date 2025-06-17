/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/17 22:59:16 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data		data;

	(void)argc;
	(void)argv;
	init_signals();
	init_data(&data, env);
	// while (1)
	// {
	// 	data.line = readline("minishell> ");
	// 	if (!data.line)
	// 	{
	// 		write(1, "exit\n", 5);
	// 		rl_clear_history();
	// 		free_and_exit(&data);
	// 	}
	// 	add_history(data.line);
	// 	printf("\n\n=== pars ===\n\n");
	// 	init_tokens(&data);
		printf("\n\n=== faker ===\n\n");
		init_builtin_cmd_multi_redir_in_multi_heredoc_multi_redir_out_append(&data);
		printf("\n\n=== exec ===\n\n");
		exec(&data);
	// }
	// jamais execute
	free_all(&data);
	return (0);
}
