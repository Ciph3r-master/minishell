/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 08:46:16 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-20 08:46:16 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*li;
	t_list	*temp;

	li = *lst;
	while (li != NULL)
	{
		temp = li;
		(*del)(temp->content);
		li = li->next;
		free(temp);
	}
	(*lst) = NULL;
}
