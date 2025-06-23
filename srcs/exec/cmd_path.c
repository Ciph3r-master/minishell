/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:52:24 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-19 16:52:24 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "minishell.h"
#include "libft.h"

int	special_case_directory(t_cmd_node *cmd_node)
{
	char		*cmd;

	if (!cmd_node || !cmd_node->cmd->cmd)
		return (-1);
	cmd = cmd_node->cmd->cmd;

	if (ft_strcmp(".", cmd) == 0)
	{
		printf("minishell: .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		cmd_node->cmd_exit_status = 2;
		return (-2);
	}
	if (ft_strcmp("..", cmd) == 0)
	{
		printf("..: command not found\n");
		cmd_node->cmd_exit_status = 127;
		return (-2);
	}
	return (1);
}

int	cmd_is_directory(t_cmd_node *cmd_node)
{
	struct stat	info;
	char		*cmd;
	int			exec_out;

	if (!cmd_node || !cmd_node->cmd->cmd)
		return (-1);
	cmd = cmd_node->cmd->cmd;
	exec_out = special_case_directory(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	if (stat(cmd, &info) != 0)
		return (1);
	if (S_ISDIR(info.st_mode))
	{
		printf("minishell: %s: Is a directory\n", cmd_node->cmd->cmd);
		cmd_node->cmd_exit_status = 126;
		return (-2);
	}
	return (1);
}

int	is_executable_cmd(t_cmd_node *cmd_node)
{
	if (!cmd_node || !cmd_node->cmd->cmd)
		return (-1);
	if (0 == access(cmd_node->cmd->cmd, X_OK))
	{
		cmd_node->cmd->pathname = cmd_node->cmd->cmd;
		return (1);
	}
	return (1);
}

int	find_path_with_access(char **paths, char **pathname)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (0 == access(paths[i], X_OK))
		{
			*pathname = ft_strdup(paths[i]);
			if (NULL == *pathname)
			{
				ft_free_char_tab_all(paths);
				return (-1);
			}
			return (1);
		}
		i++;
	}
	return (-2);
}

int	get_cmd_path_name(t_cmd_node *cmd_node)
{
	char	*pathname;
	char	*path;
	char	**paths;
	int		exec_out;

	pathname = NULL;
	path = getenv("PATH");
	if (NULL == path)
		return (-1);
	paths = ft_split_set(path, ":");
	if (ft_add_string_to_strings(paths, "/") == NULL)
		return (-1);
	if (ft_add_string_to_strings(paths, cmd_node->cmd->args[0]) == NULL)
		return (-1);
	exec_out = find_path_with_access(paths, &pathname);
	if (exec_out != 1)
	{
		ft_free_char_tab_all(paths);
		return (exec_out);
	}
	cmd_node->cmd->pathname = pathname;
	ft_free_char_tab_all(paths);
	return (1);
}
