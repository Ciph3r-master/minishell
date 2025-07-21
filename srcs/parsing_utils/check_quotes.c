/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:35:08 by vscode            #+#    #+#             */
/*   Updated: 2025/07/22 00:16:19 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"

bool	check_quotes(char *line)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (line[i])
	{
		if (current_quote == 0 && (line[i] == '"' || line[i] == '\''))
			current_quote = line[i];
		else if (line[i] == current_quote)
			current_quote = 0;
		i++;
	}
	if (current_quote != 0)
	{
		write(STDERR_FILENO, "minishell: error: unclosed quotes\n", 35);
		return (false);
	}
	return (true);
}
