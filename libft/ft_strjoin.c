/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 07:24:11 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-12 07:24:11 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	join_len;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	join_len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof (*s1) * join_len + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = 0;
	while (s1 != NULL && s1[++i])
		join[i] = s1[i];
	while (s2 != NULL && s2[j])
	{
		join[i] = s2[j];
		j++;
		i++;
	}
	join[i] = '\0';
	return (join);
}
