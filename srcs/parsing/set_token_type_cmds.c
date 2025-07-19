/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:47:20 by billcipher        #+#    #+#             */
/*   Updated: 2025/06/30 20:53:47 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	set_builtin(t_tokenlist *tl)
{
	t_tokenlist	*current;

	current = tl;
	while (current)
	{
		if (current->type == TEXTERN)
		{
			if (!current->token)
				return ;
			if (is_builtin(current->token))
				current->type = TBUILTIN;
		}
		current = current->next;
	}
}

void	set_cmd(t_tokenlist *tl)
{
	t_tokenlist	*current;

	current = tl;
	while (current)
	{
		if (current->type == TRD_IN
			|| current->type == TRD_OUT
			|| current->type == TAPPEND
			|| current->type == THD
			|| current->type == TFILE
			|| current->type == TLIMITER
			|| current->type == TSPACE
			|| current->type == TPIPE)
		{
			if (current->type == TBUILTIN)
				break ;
			current = current->next;
			continue ;
		}
		current->type = TEXTERN;
		break ;
	}
}

void	set_cmds(t_tokenlist *tl)
{
	t_tokenlist	*current;

	current = tl;
	set_cmd(tl);
	while (current)
	{
		if (current->next && current->type == TPIPE)
			set_cmd(current);
		current = current->next;
	}
}

void	set_args(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokentype	type;

	current = tl;
	while (current)
	{
		type = current->type;
		if (type == TWORD || type == TDQUOTES || type == TQUOTES)
			current->type = TARG;
		if ((type == TEXTERN || type == TBUILTIN)
			&& current->next != NULL
			&& current->next->type != TRD_IN
			&& current->next->type != TRD_OUT
			&& current->next->type != TRD_IN
			&& current->next->type != TAPPEND
			&& current->next->type != THD
			&& current->next->type != TPIPE
			&& current->next->type != TSPACE)
			current->next->type = TARG;
		current = current->next;
	}
}
