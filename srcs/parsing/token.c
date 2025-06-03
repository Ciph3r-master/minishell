/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/03 21:12:03 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

char	*get_token(char *line)
{
	char	*token;
	char	in_quote;
	int		start;
	int		len;
	
	in_quote = 0;
	start = 0;
	len = 1;
	while (line[start] && ft_is_white_space(line[start]))
		start++;
	if (line[start] == '"' || line[start] == '\'')
	{
		in_quote = line[start];
		while (line[start + len] && line[start + len] != in_quote)
			len++;
		token = ft_strndup(line, 1 + len - start);
		if (!token)
			return (NULL);
		printf("%s %d %d\n", token, len, start);
	}
	else
	{
		while (line[start + len] && !ft_is_white_space(line[start + len]) && line[start + len] != '"' && line[start + len] != '\'')
			len++;
		token = ft_strndup(line, len - start);
		// ATTENTION RETOUR D'ERREUR
		if (!token)
			return (NULL);
		printf("%s %d %d\n", token, len, start);		
	}
	return (token);
}