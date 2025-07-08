/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_saved_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:16:57 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/08 20:43:50 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	close_saved_fds(t_data *data)
{
	if (data->saved_stdin != -1)
	{
		if (close(data->saved_stdin) == -1)
			free_and_exit(data, 1);
		printf("close stdint\n");
		data->saved_stdin = -1;
	}
	if (data->saved_stdout != -1)
	{
		if (close(data->saved_stdout) == -1)
			free_and_exit(data, 1);
		printf("close stdout\n");
		data->saved_stdout = -1;
	}
	return (1);
}
