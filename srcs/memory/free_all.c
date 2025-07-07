/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:03:29 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/07 18:37:59 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_all(t_data *data, int exit_code)
{
	delete_tmp_files(data);
	if (data->env_copy)
		free_env_copy(data->env_copy);
	if (data->env_list)
		free_env_list(data->env_list);
	if (data->tokenlist)
		free_tokenlist(&data->tokenlist);
	if (data->cmd_node)
		free_cmd_list(&data->cmd_node);
	if (data->saved_stdin != -1 || data->saved_stdout != -1)
		close_saved_fds(data);
	exit(exit_code);
	return ;
}
