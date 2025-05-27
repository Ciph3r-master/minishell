/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 12:53:45 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-08 12:53:45 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		size;
	char	rchr;

	rchr = (char)c;
	size = ft_strlen(s);
	while (size != -1)
	{
		if (s[size] == rchr)
			return ((char *)&s[size]);
		size--;
	}
	return (NULL);
}
