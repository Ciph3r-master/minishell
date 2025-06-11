/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-10 16:12:35 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-10 16:12:35 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	get_key_size(int *key_size, char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i] != '=')
	{
		if (!env_line[i])
		{
			*key_size = 0;
			return ;
		}
		i++;
	}
	*key_size = i;
}

char	*get_env_key(char *env_line)
{
	char	*key;
	int		key_size;
	int		i;

	get_key_size(&key_size, env_line);
	key = malloc(sizeof(char) * (key_size + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < key_size)
	{
		key[i] = env_line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	get_value_size(int *value_size, char *env_line)
{
	int	i;
	int	j;

	i = 0;
	while (env_line[i] != '=')
		i++;
	if (!env_line[i] || !env_line[i + 1])
	{
		*value_size = 0;
		return ;
	}
	j = i;
	while (env_line[j])
		j++;
	*value_size = j - i;
	return ;
}

//a voir avec quentin
// est ce que je doit initialiser un "\0"
// sinon je vais free_and_exit
char	*get_env_value(char *env_line)
{
	char	*value;
	int		value_size;
	int		i;
	int		j;

	get_value_size(&value_size, env_line);
	value = malloc(sizeof(char) * (value_size + 1));
	if (!value)
		return (NULL);
	env_line = ft_strchr(env_line, '=');
	if (!env_line)
		return (NULL);
	i = 1;
	j = 0;
	while (env_line[i])
	{
		value[j] = env_line[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

t_env_list	*get_env_list(t_data *data, char **env)
{
	int			i;
	char		*key;
	char		*value;
	t_env_list	*new_node;

	data->env_list = NULL;
	i = 0;
	while (env[i])
	{
		key = get_env_key(env[i]);
		if (!key)
			free_and_exit(data);
		value = get_env_value(env[i]);
		if (!value)
			free_and_exit(data);
		new_node = new_node_env_list(key, value);
		if (!new_node)
			free_and_exit(data);
		push_back_env_list(&data->env_list, new_node);
		i++;
	}
	return (data->env_list);
}
