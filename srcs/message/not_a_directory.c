/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_a_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:23:42 by vscode            #+#    #+#             */
/*   Updated: 2025/07/15 18:25:26 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

void	msg_not_a_directory(t_data *data, int exit_code, char *name)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, ": Not a directory\n", 18);
	data->exit_status = exit_code;
}
