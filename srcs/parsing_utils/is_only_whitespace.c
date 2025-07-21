/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-21 21:55:00 by thmaitre          #+#    #+#             */
/*   Updated: 2025-07-21 21:55:00 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	is_only_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_white_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}
