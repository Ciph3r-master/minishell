/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-12 12:05:35 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-12 12:05:35 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_len(int n)
{
	int	itoa_len;

	itoa_len = 0;
	if (n < 0)
		itoa_len++;
	while (n != 0)
	{
		n /= 10;
		itoa_len++;
	}
	return (itoa_len);
}

char	*ft_itoa_support(int n, char *itoa, int itoa_len)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
		itoa[0] = '-';
	}
	while (itoa_len != sign)
	{
		itoa[itoa_len - 1] = n % 10 + 48;
		n /= 10;
		itoa_len--;
	}
	return (itoa);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		itoa_len;

	if (n == -2147483648)
	{
		itoa = ft_strdup("-2147483648");
		return (itoa);
	}
	if (n == 0)
	{
		itoa = ft_strdup("0");
		return (itoa);
	}
	itoa_len = ft_itoa_len(n);
	itoa = malloc(sizeof(*itoa) * itoa_len + 1);
	if (!itoa)
		return (NULL);
	itoa[itoa_len] = '\0';
	itoa = ft_itoa_support(n, itoa, itoa_len);
	return (itoa);
}
