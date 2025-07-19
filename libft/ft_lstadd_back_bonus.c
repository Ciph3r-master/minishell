/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-19 11:56:32 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-19 11:56:32 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*li;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	li = *lst;
	while (li->next != NULL)
	{
		li = li->next;
	}
	li->next = new;
}
