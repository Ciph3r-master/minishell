/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:00:32 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/08 19:39:48 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

void	redir_in_message(char *filename, int err)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	if (err == ENOENT)
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	else if (err == EACCES)
		write(STDERR_FILENO, ": Permission denied\n", 20);
	else
		write(STDERR_FILENO, ": Error\n", 8);
	return ;
}
