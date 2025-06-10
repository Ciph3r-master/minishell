/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-10 15:44:17 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-10 15:44:17 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//faire la gestion des erreur
int	init_data(t_data *data, char **env)
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
		value = get_env_value(env[i]);
		new_node = new_node_env_list(key, value);
		push_back_env_list(&data->env_list, new_node);
		i++;
	}
	print_env_list(&data->env_list);
	return (0);
}
