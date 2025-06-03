/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/03 19:00:42 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		get_token(line);
		if (is_open_quotes(line, '"') || is_open_quotes(line, '\''))
		{
			printf("Open quote\n");
			continue ;
		}
	}
	rl_clear_history();
	return (0);
}
