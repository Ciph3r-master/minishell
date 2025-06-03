/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/04 01:29:19 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_operator(char *line)
{
	if (!line)
		return (0);
	if (line[0] == '|')
		return (1);
	if (line[0] == '<')
	{
		if (line[1] == '<')
			return (2);
		return (1);
	}
	if (line[0] == '>')
	{
		if (line[1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

static char	*ft_strndup(const char *src, int size)
{
	char	*dup;
	int		i;

	if (size == 0)
		return (NULL);
	i = 0;
	dup = (char *) malloc(sizeof(char) * size + 1);
	if (!dup)
		return (NULL);
	while (src[i] && i < size)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*get_token(char	*line, int	*pos)
{
	char	*token;
	char	in_quote;
	int		start;
	int		len;
	
	in_quote = 0;
	start = *pos;
	len = 0;
	while (line[start] && ft_is_white_space(line[start]))
		start++;
	if (!line[start])
		return (NULL);
	if (is_operator(&line[start]))
	{
		len = is_operator(&line[start]);
		token = ft_strndup(&line[start], len);
		if (!token)
			return (NULL);
		*pos = start + len;
		return (token);
	}
	if (line[start] == '"' || line[start] == '\'')
	{
		len = 1;
		in_quote = line[start];
		while (line[start + len] && line[start + len] != in_quote)
		{
			if (is_operator(&line[start + len]))
				break;
			len++;
		}
		token = ft_strndup(&line[start + 1], len - 1);
		if (!token)
			return (NULL);
		*pos = start + len + 1;
	}
	else
	{
		while (line[start + len] && !ft_is_white_space(line[start + len]) && line[start + len] != '"' && line[start + len] != '\'')
		{
			if (is_operator(&line[start + len]))
				break;
			len++;
		}
		token = ft_strndup(&line[start], len);
		// ATTENTION RETOUR D'ERREUR
		if (!token)
			return (NULL);
		*pos = start + len;
	}
	return (token);
}

int	init_tokens(char *line)
{
	int		pos;
	char	*token;

	pos = 0;
	token = get_token(line, &pos);
	while (token)
	{
		printf("token: [%s]\n", token);
		token = get_token(line, &pos);
	}
	return (0);
}
