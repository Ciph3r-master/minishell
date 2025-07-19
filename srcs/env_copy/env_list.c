/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:58:16 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/18 21:34:28 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_env_list	*new_node_env_list(t_data *data, char *key, char *value)
{
	t_env_list	*new_node;

	if (!value)
	{
		free(key);
		free_and_exit(data, 1);
	}
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

void	print_env_list(t_env_list **env_list)
{
	t_env_list	*cur;
	int			i;

	if (*env_list == NULL)
	{
		printf("NULL - empty_list\n");
		return ;
	}
	cur = *env_list;
	i = 0;
	while (cur)
	{
		printf("env_list[%d]->key : %s, value : %s\n", i, cur->key, cur->value);
		cur = cur->next;
		i++;
	}
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
