/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:35:08 by vscode            #+#    #+#             */
/*   Updated: 2025/07/18 23:36:34 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
