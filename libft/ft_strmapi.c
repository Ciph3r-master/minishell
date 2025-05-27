/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-13 07:03:56 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-13 07:03:56 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mapi;

	i = 0;
	mapi = ft_strdup(s);
	if (!mapi)
		return (NULL);
	while (mapi[i])
	{
		mapi[i] = (*f)(i, mapi[i]);
		i++;
	}
	return (mapi);
}
