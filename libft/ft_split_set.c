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

static char	*ft_strndup_set(char *str, int n)
{
	char	*dup;
	int		i;

	dup = malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static void	assign_split_set(char *str, char *set, char **split)
{
	int	end;
	int	beg;
	int	word;

	beg = 0;
	word = 0;
	while (str[beg])
	{
		while (is_separator(str[beg], set) && str[beg] != '\0')
			beg++;
		end = beg;
		while (!is_separator(str[end], set) && str[end] != '\0')
			end++;
		if (end > beg)
		{
			split[word] = ft_strndup_set(&str[beg], end - beg);
			if (!split[word])
			{
				free_char_tab(split, word - 1);
				return ;
			}
			word++;
		}
		beg = end;
	}
}

char	**ft_split_set(char *str, char *set)
{
	int		count_words;
	char	**split;

	if (!str || !set)
		return (NULL);
	count_words = ft_count_words_set(str, set);
	split = malloc(sizeof(char *) * (count_words + 1));
	if (!split)
		return (NULL);
	assign_split_set(str, set, split);
	split[count_words] = NULL;
	return (split);
}
