/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/05 21:11:08 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	// char		*line;
	t_data		data;

	init_data(&data, env);
	(void)argc;
	(void)argv;
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	add_history(line);
	// 	init_tokens(line);
	// }
	// rl_clear_history();
	free_all(&data);
	return (0);
}
