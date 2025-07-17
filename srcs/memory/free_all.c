/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:03:29 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/10 00:27:00 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	free_all(t_data *data, int exit_code)
{
	if (exit_code != -1)
		delete_tmp_files(data);
	if (exit_code == -1)
		exit_code = 0;
	if (data->env_copy)
		free_env_copy(data->env_copy);
	if (data->env_list)
		free_env_list(data->env_list);
	if (data->tokenlist)
		free_tokenlist(&data->tokenlist);
	if (data->cmd_node)
		free_cmd_list(&data->cmd_node);
	// printf("free_all\n");
	// printf("data->saved_stdin :%d\n", data->saved_stdin);
	// printf("data->saved_stdout :%d\n", data->saved_stdout);
	if (data->saved_stdin != -1 || data->saved_stdout != -1)
		close_saved_fds(data);
	exit(exit_code);
	return ;
}
