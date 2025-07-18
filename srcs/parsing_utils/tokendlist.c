/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokendlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:13:38 by bill              #+#    #+#             */
/*   Updated: 2025/07/18 19:17:29 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_tokenlist	*tokenlist_create_node(t_data *data, void *content,
	t_tokentype type)
{
	t_tokenlist	*node;

	node = malloc(sizeof(t_tokenlist));
	if (!node)
	{
		if (content)
			free(content);
		free_and_exit(data, 1);
	}
	node->prev = NULL;
	node->next = NULL;
	node->token = content;
	node->type = type;
	return (node);
}

t_tokenlist	*tokenlist_push_front(t_data *data, t_tokenlist **tokenlist,
	void *content, t_tokentype type)
{
	t_tokenlist	*tmp;
	t_tokenlist	*new_node;

	if (!tokenlist)
		return (NULL);
	new_node = tokenlist_create_node(data, content, type);
	if (!new_node)
		return (NULL);
	if (!*tokenlist)
	{
		*tokenlist = new_node;
		return (new_node);
	}
	tmp = *tokenlist;
	*tokenlist = new_node;
	tmp->prev = new_node;
	new_node->next = tmp;
	return (*tokenlist);
}

t_tokenlist	*tokenlist_push_back(t_data *data, t_tokenlist **tokenlist,
	void *content, t_tokentype type)
{
	t_tokenlist	*new_node;
	t_tokenlist	*current;

	if (!tokenlist)
		return (NULL);
	new_node = tokenlist_create_node(data, content, type);
	if (!new_node)
		return (NULL);
	if (*tokenlist == NULL)
	{
		*tokenlist = new_node;
		return (new_node);
	}
	current = *tokenlist;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
	return (*tokenlist);
}

t_tokenlist	*tokenlist_insert_after(t_data *data, t_tokenlist *node,
	void *content, t_tokentype type)
{
	t_tokenlist	*new_node;

	if (!node)
		return (NULL);
	new_node = tokenlist_create_node(data, content, type);
	if (!new_node)
		return (NULL);
	new_node->next = node->next;
	new_node->prev = node;
	if (node->next)
		node->next->prev = new_node;
	node->next = new_node;
	return (new_node);
}

void	tokenlist_remove_node(t_tokenlist **head, t_tokenlist *node)
{
	if (!head || !*head || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->token);
	free(node);
}
