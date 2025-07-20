/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:29:56 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/21 01:51:01 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static t_tokentype	get_operator_type(t_tokenlist *current)
{
	if (!current || current->type == TDQUOTES
		|| current->type == TQUOTES || !current->token)
		return (TUNKNOWN);
	if (current->token[0] == '|')
		return (TPIPE);
	if (current->token[0] == '<')
	{
		if (current->token[1] == '<')
			return (THD);
		else
			return (TRD_IN);
	}
	if (current->token[0] == '>')
	{
		if (current->token[1] == '>')
			return (TAPPEND);
		else
			return (TRD_OUT);
	}
	return (TUNKNOWN);
}

void	print_syntax_error(char *token)
{
	const char	*prefix = "minishell: syntax error near unexpected token `";

	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, "'\n", 2);
}

bool	is_invalid_redir(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokenlist	*next;

	current = tl;
	while (current)
	{
		if (is_redirection(get_operator_type(current)))
		{
			next = current->next;
			if (next && next->type == TSPACE)
				next = next->next;
			if (!next || is_redirection(get_operator_type(next))
				|| get_operator_type(next) == TPIPE)
			{
				if (!next)
					print_syntax_error(current->token);
				else
					print_syntax_error(next->token);
				return (true);
			}
		}
		current = current->next;
	}
	return (false);
}

bool	check_pipe_error(t_tokenlist *next)
{
	if (!next)
	{
		print_syntax_error("|");
		return (true);
	}
	if (!next || get_operator_type(next) == TPIPE)
	{
		print_syntax_error("|");
		return (true);
	}
	return (false);
}

bool	is_invalid_pipe(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokenlist	*next;

	current = tl;
	if (current && get_operator_type(current) == TPIPE)
	{
		print_syntax_error("|");
		return (true);
	}
	while (current)
	{
		if (get_operator_type(current) == TPIPE)
		{
			next = current->next;
			if (next && next->type == TSPACE)
				next = next->next;
			if (check_pipe_error(next))
				return (true);
		}
		current = current->next;
	}
	return (false);
}
