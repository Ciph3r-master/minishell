/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:29:56 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/19 05:17:59 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "libft.h"

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
