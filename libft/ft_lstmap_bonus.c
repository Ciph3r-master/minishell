/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-20 13:20:41 by thmaitre          #+#    #+#             */
/*   Updated: 2024-11-20 13:20:41 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin_map;
	t_list	*element;

	begin_map = NULL;
	element = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		element = ft_lstnew(lst->content);
		if (element == NULL)
		{
			ft_lstclear(&begin_map, del);
			return (NULL);
		}
		ft_lstadd_back(&begin_map, element);
		element->content = (*f)(lst->content);
		lst = lst->next;
	}
	return (begin_map);
}
