/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:52:24 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:14 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
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
	if (stat(cmd, &info) != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd, strlen(cmd));
		write(STDERR_FILENO, ": Is a directory\n", 17);
		data->exit_status = 126;
	}
	return (1);
}

int	is_cmd_name_executable(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	if (0 == access(cmd_node->cmd->cmd, X_OK))
		cmd_node->cmd->pathname = cmd_node->cmd->cmd;
	return (1);
}

int	find_path_with_access(char **paths, char **pathname,
	t_data *data, t_cmd_node *cmd_node)
{
	char	*cmd;
	int		i;

	cmd = cmd_node->cmd->cmd;
	i = 0;
	while (paths[i] && cmd[0])
	{
		if (0 == access(paths[i], X_OK))
		{
			*pathname = ft_strdup(paths[i]);
			if (NULL == *pathname)
			{
				ft_free_char_tab_all(paths);
				free_and_exit(data, 1);
			}
			return (1);
		}
		i++;
	}
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	data->exit_status = 127;
	return (0);
}

int	get_cmd_path_name(t_cmd_node *cmd_node, t_data *data)
{
	char	*pathname;
	char	*path;
	char	**paths;

	pathname = NULL;
	path = getenv("PATH");
	if (NULL == path)
		free_and_exit(data, 1);
	paths = ft_split_set(path, ":");
	if (!paths)
		free_and_exit(data, 1);
	if (ft_add_string_to_strings(paths, "/") == NULL)
		free_and_exit(data, 1);
	if (ft_add_string_to_strings(paths, cmd_node->cmd->args[0]) == NULL)
		free_and_exit(data, 1);
	find_path_with_access(paths, &pathname, data, cmd_node);
	ft_free_char_tab_all(paths);
	cmd_node->cmd->pathname = pathname;
	return (1);
}
