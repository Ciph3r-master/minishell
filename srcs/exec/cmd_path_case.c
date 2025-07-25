/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-24 20:30:49 by thmaitre          #+#    #+#             */
/*   Updated: 2025-07-24 20:30:49 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "minishell.h"
#include "libft.h"

int	special_case_directory(t_cmd_node *cmd_node, t_data *data)
{
	char		*cmd;

	if (!cmd_node || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	cmd = cmd_node->cmd->cmd;
	if (ft_strcmp(".", cmd) == 0)
	{
		write(STDERR_FILENO, "minishell: .: filename argument required\n", 41);
		write(STDERR_FILENO, ".: usage: . filename [arguments]\n", 33);
		data->exit_status = 2;
	}
	if (ft_strcmp("..", cmd) == 0)
	{
		write(STDERR_FILENO, "..: command not found\n", 22);
		data->exit_status = 127;
	}
	return (1);
}

int	cmd_is_directory(t_cmd_node *cmd_node, t_data *data)
{
	struct stat	info;
	char		*cmd;

	if (!cmd_node || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	cmd = cmd_node->cmd->cmd;
	special_case_directory(cmd_node, data);
	if (stat(cmd, &info) != 0 || data->exit_status != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": Is a directory\n", 17);
		data->exit_status = 126;
	}
	return (1);
}
