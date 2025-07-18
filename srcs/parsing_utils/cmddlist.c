/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmddlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:11:33 by bill              #+#    #+#             */
/*   Updated: 2025/07/18 19:18:11 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_cmd_node	*cmdlist_create_node(t_data *data)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_cmd_node));
	if (!node)
		free_and_exit(data, 1);
	node->cmd = NULL;
	node->file_in = NULL;
	node->file_out = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->type = 0;
	node->cmd_exit_status = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cmd_node	*cmdlist_push_front(t_data *data, t_cmd_node **cmdlist)
{
	t_cmd_node	*tmp;
	t_cmd_node	*new_node;

	if (!cmdlist)
		return (NULL);
	new_node = cmdlist_create_node(data);
	if (!new_node)
		return (NULL);
	if (!*cmdlist)
	{
		*cmdlist = new_node;
		return (new_node);
	}
	tmp = *cmdlist;
	*cmdlist = new_node;
	tmp->prev = new_node;
	new_node->next = tmp;
	return (*cmdlist);
}

t_cmd_node	*cmdlist_push_back(t_data *data, t_cmd_node **cmdlist)
{
	t_cmd_node	*new_node;
	t_cmd_node	*current;

	if (!cmdlist)
		return (NULL);
	new_node = cmdlist_create_node(data);
	if (!new_node)
		return (NULL);
	if (*cmdlist == NULL)
	{
		*cmdlist = new_node;
		return (new_node);
	}
	current = *cmdlist;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
	return (*cmdlist);
}

t_cmd_node	*cmdlist_getlast(t_cmd_node *cmdlist)
{
	t_cmd_node	*current;

	if (!cmdlist)
		return (NULL);
	current = cmdlist;
	while (current && current->next)
		current = current->next;
	return (current);
}
