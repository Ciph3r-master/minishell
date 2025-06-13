/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:38:08 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/13 17:39:01 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_and_exit(t_data *data)
{
	delete_tmp_files(data);
	if (data->env_copy)
		free_env_copy(data->env_copy);
	if (data->env_list)
		free_env_list(data->env_list);
	// free_pathnames(data);
	exit(EXIT_FAILURE);
	return ;
}
