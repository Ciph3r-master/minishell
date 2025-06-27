/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:48:30 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/27 14:56:02 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int count_args(t_tokenlist *tl)
{
	t_tokenlist *current;
	int ac;

	ac = 0;
	current = tl;
	while (current && current->type != TPIPE)
	{
		if (current->type == TARG || current->type == TEXTERN || current->type == TBUILTIN)
			ac++;
		current = current->next;
	}
	return (ac);
}

t_cmd *init_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	// FREE AND EXIT
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->pathname = NULL;
	return (cmd);
}

int	init_args(t_tokenlist *start, t_cmd *cmd)
{
	char **args;

	args = malloc(sizeof(char *) * (count_args(start) + 2));
	if (!args)
		return (0);
	args[0] = NULL;
	cmd->args = args;
	return (1);
}
