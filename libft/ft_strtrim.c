/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 07:56:44 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-12 07:56:44 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_find_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (ft_in_set(s1[start], set))
		start++;
	return (start);
}

static int	ft_find_end(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (ft_in_set(s1[end], set))
		end--;
	return (end + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		trim_start;
	int		trim_end;
	int		i;

	trim_start = ft_find_start(s1, set);
	trim_end = ft_find_end(s1, set);
	if (trim_end - trim_start <= 0)
		trim = malloc(sizeof(*s1));
	else
		trim = malloc(sizeof(*s1) * (trim_end - trim_start) + 1);
	if (!trim)
		return (NULL);
	i = 0;
	while (trim_start < trim_end)
	{
		trim[i] = s1[trim_start];
		trim_start++;
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
