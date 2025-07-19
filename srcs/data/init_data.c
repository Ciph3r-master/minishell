/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:44:17 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 03:28:22 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	data->env_list = get_env_list(data, env);
	sh_level(data);
	data->env_copy = get_env_copy(data->env_list);
	if (!data->env_copy)
		free_and_exit(data, 1);
	data->exec_heredoc = 1;
	data->exit_status = 0;
	data->prev_exit_status = 0;
	data->cmd_node = NULL;
	data->tokenlist = NULL;
	data->line = NULL;
	data->pwd = NULL;
	data->old_pwd = NULL;
	return (0);
}
