/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:03:29 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/17 22:30:33 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_all(t_data *data)
{
	delete_tmp_files(data);
	if (data->env_copy)
		free_env_copy(data->env_copy);
	if (data->env_list)
		free_env_list(data->env_list);
	if (data->tokenlist)
		free_tokenlist(&data->tokenlist);
	exit(EXIT_SUCCESS);
	return ;
}
