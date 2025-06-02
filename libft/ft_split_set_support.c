/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niroched <niroched@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:35:59 by thmaitre          #+#    #+#             */
/*   Updated: 2025/04/30 11:12:20 by niroched         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_char_tab_set(char **split, int k)
{
	while (k >= 0)
	{
		free(split[k]);
		k--;
	}
	free(split);
	return (NULL);
}

int	is_separator(char c, char *set)
{
	return (ft_strchr(set, c) != NULL);
}

int	ft_count_words_set(char *str, char *set)
{
	int	is_word;
	int	count;
	int	i;

	is_word = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (!is_separator(str[i], set) && str[i] != '\0')
		{
			if (is_word == 0)
			{
				is_word = 1;
				count++;
			}
			i++;
		}
		if (str[i] != '\0')
			i++;
		is_word = 0;
	}
	return (count);
}
