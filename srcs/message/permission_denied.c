/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_denied.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:17:33 by vscode            #+#    #+#             */
/*   Updated: 2025/07/15 18:26:02 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

void	msg_permission_denied(t_data *data, int exit_code, char *name)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, ": Permission denied\n", 20);
	data->exit_status = exit_code;
}
