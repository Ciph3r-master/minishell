/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_string_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 13:56:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-11 13:56:13 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_string_to_strings(char **strings, char *string)
{
	int		i;
	char	*new_str;

	if (!strings || !string)
		return (NULL);
	i = 0;
	new_str = NULL;
	while (strings[i])
	{
		new_str = ft_strjoin(strings[i], string);
		if (!new_str)
			return (NULL);
		free(strings[i]);
		strings[i] = new_str;
		i++;
	}
	return (strings);
}
