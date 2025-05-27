/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 14:21:59 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-08 14:21:59 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*mem_s;
	char		mem_c;

	i = 0;
	mem_s = (char *)s;
	mem_c = (char)c;
	while (i < n)
	{
		if (mem_s[i] == mem_c)
			return ((void *)&mem_s[i]);
		i++;
	}
	return (NULL);
}
