/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:38:08 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/08 06:22:32 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	free_and_exit_debug(t_data *data, int exit_code, const char *file, int line)
{
	(void)file;
	(void)line;
	printf("exit_code : %d at %s:%d\n", exit_code, file, line);
	free_all(data, exit_code);
	return ;
}
