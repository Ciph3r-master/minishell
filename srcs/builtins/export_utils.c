/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:00:07 by bill              #+#    #+#             */
/*   Updated: 2025/07/25 22:28:18 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	update_env_cpy(t_data *data)
{
	free_env_copy(data->env_copy);
	data->env_copy = get_env_copy(data->env_list);
}

char	*get_key(t_data *data, char *arg)
{
	int		len;
	char	*key;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	key = ft_substr(arg, 0, len);
	if (!key)
		free_and_exit(data, 1);
	return (key);
}

void	sort_env(t_data *data, char **env)
{
	int		i;
	char	*temp;
	char	*key1;
	char	*key2;

	i = 0;
	while (env[i] && env[i + 1])
	{
		key1 = get_key(data, env[i]);
		key2 = get_key(data, env[i + 1]);
		if (ft_strcmp(key1, key2) > 0)
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
		free(key1);
		free(key2);
	}
}

t_env_list	*get_env_by_key(t_data *data, char *key)
{
	t_env_list	*current;

	current = data->env_list;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_new_var(t_data *data, char *key, char *value, bool is_null)
{
	t_env_list	*new_node;

	if (is_null == false && value == NULL)
	{
		free(key);
		free_and_exit(data, 1);
	}
	new_node = new_node_env_list_export(data, key, value);
	if (!new_node)
	{
		free(key);
		free_and_exit(data, 1);
	}
	push_back_env_list(&data->env_list, new_node);
}
