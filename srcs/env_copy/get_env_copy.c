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

void	strdup_keys(char **env_copy, t_env_list *env_list)
{
	t_env_list	*current;
	int			i;

	current = env_list;
	i = 0;
	while (current->next)
	{
		env_copy[i] = ft_strdup(current->key);
		current = current->next;
		i++;
	}
	return ;
}

void	join_values(char **env_copy, t_env_list *env_list)
{
	t_env_list	*current;
	char		*new_str;
	int			i;

	current = env_list;
	i = 0;
	while (current->next)
	{
		new_str = ft_strjoin(env_copy[i], current->value);
		if (!new_str)
			return ;
		free(env_copy[i]);
		env_copy[i] = new_str;
		current = current->next;
		i++;
	}
	return ;
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

	env_list_size = get_env_list_size(env_list);
	env_copy = malloc(sizeof(char *) * (env_list_size + 1));
	if (!env_copy)
		return (NULL);
	env_copy[env_list_size] = NULL;
	strdup_keys(env_copy, env_list);
	ft_add_string_to_strings(env_copy, "=");
	join_values(env_copy, env_list);
	return (env_copy);
}
