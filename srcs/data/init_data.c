/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:44:17 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/17 19:13:00 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	data->env_list = get_env_list(data, env);
	data->env_copy = get_env_copy(data->env_list);
	data->exit_status = 0;
	if (!data->env_copy)
		free_and_exit(data);
	data->cmd_node = NULL;
	data->tokenlist = NULL;
	data->line = NULL;
	data->pwd = NULL;
	data->old_pwd = NULL;
	return (0);
}
