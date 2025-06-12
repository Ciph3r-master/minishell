/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 13:17:18 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-11 13:17:18 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**strdup_keys(char **env_copy, t_env_list *env_list)
{
	t_env_list	*current;
	int			i;

	current = env_list;
	i = 0;
	while (current)
	{
		env_copy[i] = ft_strdup(current->key);
		if (!env_copy[i])
			return (NULL);
		current = current->next;
		i++;
	}
	return (env_copy);
}

char	**join_values(char **env_copy, t_env_list *env_list)
{
	t_env_list	*current;
	char		*new_str;
	int			i;

	current = env_list;
	i = 0;
	while (current)
	{
		new_str = ft_strjoin(env_copy[i], current->value);
		if (!new_str)
			return (NULL);
		free(env_copy[i]);
		env_copy[i] = new_str;
		current = current->next;
		i++;
	}
	return (env_copy);
}

void	print_env_copy(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		printf("%s\n", env_copy[i]);
		i++;
	}
	return ;
}

char	**get_env_copy(t_env_list *env_list)
{
	char	**env_copy;
	int		env_list_size;

	if (!env_list)
		return (NULL);
	env_list_size = get_env_list_size(env_list);
	env_copy = malloc(sizeof(char *) * (env_list_size + 1));
	if (!env_copy)
		return (NULL);
	env_copy[env_list_size] = NULL;
	env_copy = strdup_keys(env_copy, env_list);
	if (!env_copy)
		return (NULL);
	env_copy = ft_add_string_to_strings(env_copy, "=");
	if (!env_copy)
		return (NULL);
	env_copy = join_values(env_copy, env_list);
	if (!env_copy)
		return (NULL);
	return (env_copy);
}
