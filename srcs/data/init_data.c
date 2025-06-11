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

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

	#include <stdio.h>

//faire la gestion des erreur
int	init_data(t_data *data, char **env)
{
	data->env_list = get_env_list(data, env);
	print_env_list(&data->env_list);
	data->env_copy = get_env_copy(data->env_list);
	if (!data->env_copy)
		free_and_exit(data);
	print_env_copy(data->env_copy);
	return (0);
}
