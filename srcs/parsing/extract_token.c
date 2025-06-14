/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:17:18 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/14 19:21:30 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_tokenlist	*extract_space(t_tokenlist *tl, char *line, int *pos)
{
	int			len;

	len = 0;
	while (line[*pos + len] && ft_is_white_space(line[*pos + len]))
		len++;
	*pos += len;
	if (len > 0)
		return (tokenlist_push_back(&tl, NULL, TSPACE));
	return (tl);
}

t_tokenlist	*extract_operator(t_tokenlist *tl, char *line, int *pos)
{
	int			len;
	t_tokenlist	*ntl;

	len = is_operator(&line[*pos]);
	ntl = tokenlist_push_back(&tl, ft_strndup(&line[*pos], len), TOPERATOR);
	*pos += len;
	return (ntl);
}

t_tokenlist	*extract_quotes(t_tokenlist *tl, char *line, int *pos)
{
	int		len;
	char	in_quote;
	int		start;

	len = 1;
	in_quote = line[*pos];
	(*pos)++;
	start = *pos;
	if (line[start] == in_quote)
	{
		(*pos)++;
		return (tokenlist_push_back(&tl, ft_strndup("", 1), TDQUOTES));
	}
	while (line[start + len] && line[start + len] != in_quote)
		len++;
	*pos = start + len + 1;
	if (in_quote == '"')
		return (tokenlist_push_back(&tl, ft_strndup(&line[start], len), TDQUOTES));
	else
		return (tokenlist_push_back(&tl, ft_strndup(&line[start], len), TQUOTES));
}

t_tokenlist	*extract_word(t_tokenlist *tl, char *line, int *pos)
{
	int	start;
	int	len;

	start = *pos;
	len = 0;
	while (line[start + len]
		&& !ft_is_white_space(line[start + len])
		&& line[start + len] != '"' && line[start + len] != '\'')
	{
		if (is_operator(&line[start + len]))
			break ;
		len++;
	}
	*pos = start + len;
	return (tokenlist_push_back(&tl, ft_strndup(&line[start], len), TWORD));
}
