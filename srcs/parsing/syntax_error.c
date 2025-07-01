/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:29:56 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/01 18:28:37 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
}

bool	is_invalid_redir(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokenlist	*next;

	current = tl;
	while (current)
	{
		if (is_redirection(current->type))
		{
			next = current->next;
			if (next && current->next->type == TSPACE)
				next = next->next;
			if (!next || is_redirection(next->type) || next->type == TPIPE)
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
	if (next->type == TPIPE)
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
	if (current && current->type == TPIPE)
	{
		print_syntax_error("|");
		return (true);
	}
	while (current)
	{
		if (current->type == TPIPE)
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
