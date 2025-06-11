/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 17:03:29 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-11 17:03:29 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_all(t_data *data)
{
	if (data->env_copy)
		free_env_copy(data->env_copy);
	if (data->env_list)
		free_env_list(data->env_list);
	exit(EXIT_SUCCESS);
	return ;
}
