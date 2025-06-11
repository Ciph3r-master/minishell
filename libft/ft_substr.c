/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:06:01 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/11 20:36:14 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_support(char *sub, char const *s,
	unsigned int start, size_t len)
{
	size_t		sub_len;
	size_t		i;

	i = 0;
	sub_len = ft_strlen(&s[start]);
	if (sub_len < len)
		sub = malloc(sizeof(*s) * sub_len + 1);
	else if (sub_len >= len)
		sub = malloc(sizeof(*s) * len + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;

	sub = NULL;
	if ((size_t)start > ft_strlen(s))
	{
		sub = malloc(sizeof(*s));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = ft_substr_support(sub, s, start, len);
	return (sub);
}
