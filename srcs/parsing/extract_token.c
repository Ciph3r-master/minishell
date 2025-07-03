/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:17:18 by qutruche          #+#    #+#             */
/*   Updated: 2025/07/02 18:42:18 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//TODO GERER LES FREE
void	merge_token(t_tokenlist **tl)
{
	t_tokenlist	*current;
	char		*tmp;

	current = *tl;
	while (current && current->next)
	{
		if (current->type != TSPACE && current->next->type != TSPACE
			&& current->type != TOPERATOR && current->next->type != TOPERATOR)
		{
			tmp = current->token;
			current->token = ft_strjoin(current->token, current->next->token);
			tokenlist_remove_node(tl, current->next);
			free(tmp);
		}
		else
			current = current->next;
	}
}

t_tokenlist	*extract_space(t_data *data, t_tokenlist *tl, char *line, int *pos)
{
	int			len;

	len = 0;
	while (line[*pos + len] && ft_is_white_space(line[*pos + len]))
		len++;
	*pos += len;
	if (len > 0)
		return (tokenlist_push_back(data, &tl, NULL, TSPACE));
	return (tl);
}

t_tokenlist	*extract_operator(t_data *data, t_tokenlist *tl, char *line, int *pos)
{
	int			len;
	t_tokenlist	*ntl;

	len = is_operator(&line[*pos]);
	ntl = tokenlist_push_back(data, &tl, ft_strndup(&line[*pos], len), TOPERATOR);
	*pos += len;
	return (ntl);
}

t_tokenlist	*extract_quotes(t_data *data, t_tokenlist *tl, char *line, int *pos)
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
		return (tokenlist_push_back(data, &tl, ft_strndup("", 1), TDQUOTES));
	}
	while (line[start + len] && line[start + len] != in_quote)
		len++;
	*pos = start + len + 1;
	if (in_quote == '"')
		return (tokenlist_push_back(data, &tl, ft_strndup(&line[start], len), TDQUOTES));
	else
		return (tokenlist_push_back(data, &tl, ft_strndup(&line[start], len), TQUOTES));
}

t_tokenlist	*extract_word(t_data *data, t_tokenlist *tl, char *line, int *pos)
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
	return (tokenlist_push_back(data, &tl, ft_strndup(&line[start], len), TWORD));
}
