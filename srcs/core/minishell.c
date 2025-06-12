/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/12 17:23:35 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

	#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_data		data;

	(void)argc;
	(void)argv;
	init_signals();
	init_data(&data, env);
	faker();
	exec(&data);
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 	{
	// 		write(1, "exit\n", 5);
	// 		free_and_exit(&data);
	// 	}
	// 	add_history(line);
	// 	init_tokens(line, data.env_list);
	// }
	// rl_clear_history();
	free_all(&data);
	return (0);
}
