/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:58:16 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/25 22:34:35 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

t_env_list	*new_node_env_list(t_data *data, char *key, char *value)
{
	t_env_list	*new_node;

	//if (!value)
	//{
	//	free(key);
	//	free_and_exit(data, 1);
	//}
	(void) data;
	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	push_back_env_list(t_env_list **env_list, t_env_list *new_node)
{
	t_env_list	*current;

	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return ;
}

int	get_env_list_size(t_env_list *env_list)
{
	int			env_list_size;
	t_env_list	*current;

	env_list_size = 0;
	current = env_list;
	while (current)
	{
		current = current->next;
		env_list_size++;
	}
	return (env_list_size);
}
