/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:23:56 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/19 18:56:52 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_operator(t_tokenlist *tl)
{
	t_tokenlist	*current;

	current = tl;
	while (current)
	{
		if (current->type == TOPERATOR)
		{
			if (!current->token)
				return ;
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
		current = current->next;
	}
}

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
				break;
			current = current->next;
			continue;
		}
		current->type = TEXTERN;
		break;
	}
}

void set_cmds(t_tokenlist *tl)
{
	t_tokenlist *current;

	current = tl;
	set_cmd(tl);
	while (current)
	{
		if (current->next && current->type == TPIPE)
			set_cmd(current);
		current = current->next;
	}
}

bool is_invalid_target(t_tokentype type)
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
	while(current)
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
