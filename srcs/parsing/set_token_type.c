/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:23:56 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/14 19:24:15 by qutruche         ###   ########.fr       */
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
		if (current->type == TWORD)
		{
			if (!current->token)
				return ;
			if (is_builtin(current->token))
				current->type = TBUILTIN;
		}
		current = current->next;
	}
}
//TODO GERER AUSSI LES COMMANDES IN QUOTES arg ...
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
			current = current->next;
			continue;
		}
		current->type = TEXTERN;
		break;
	}
}

void	set_file(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokentype	type;

	current = tl;
	while (current)
	{
		type = current->type;
		if (current->next != NULL
			&& current->next->type != TRD_IN
			&& current->next->type != TAPPEND
			&& current->next->type != TRD_OUT
			&& current->next->type != THD
			&& (type == TRD_IN || type == TRD_OUT || type == TAPPEND))
		{
			if (current->next && current->next->type == TSPACE)
				current = current->next;
			if (current->next)
				current->next->type = TFILE;
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
