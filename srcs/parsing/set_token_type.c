/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:23:56 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/30 20:54:38 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static void	update_operator_type(t_tokenlist *current)
{
	if (current->token[0] == '|')
		current->type = TPIPE;
	if (current->token[0] == '<')
	{
		if (current->token[1] == '<')
			current->type = THD;
		else
			current->type = TRD_IN;
	}
	if (current->token[0] == '>')
	{
		if (current->token[1] == '>')
			current->type = TAPPEND;
		else
			current->type = TRD_OUT;
	}
}

void	set_operator(t_tokenlist *tl)
{
	t_tokenlist	*current;

	current = tl;
	while (current)
	{
		if (current->token && current->type == TOPERATOR)
			update_operator_type(current);
		current = current->next;
	}
}

bool	is_invalid_target(t_tokentype type)
{
	return (is_redirection(type) || type == TPIPE || type == TSPACE);
}

void	set_file(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokenlist	*target;

	current = tl;
	while (current)
	{
		if (is_redirection(current->type) && current->next)
		{
			target = current->next;
			if (target->type == TSPACE && target->next)
				target = target->next;
			if (!is_invalid_target(target->type))
				target->type = TFILE;
		}
		current = current->next;
	}
}

void	set_limiter(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokentype	type;

	current = tl;
	while (current)
	{
		type = current->type;
		if (type == THD
			&& current->next != NULL)
		{
			if (current->next->type == TSPACE)
				current = current->next;
			current->next->type = TLIMITER;
		}
		current = current->next;
	}
}
