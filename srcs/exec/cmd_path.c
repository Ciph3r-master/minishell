/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:52:24 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 02:48:33 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include "minishell.h"
#include "libft.h"

int	is_cmd_name_executable(t_cmd_node *cmd_node, t_data *data)
{
	if (!cmd_node || !cmd_node->cmd->cmd)
		free_and_exit(data, 1);
	if (0 == access(cmd_node->cmd->cmd, X_OK))
		cmd_node->cmd->pathname = secure_strdup(data, cmd_node->cmd->cmd);
	return (1);
}

int	path_access_loop(char **paths, char **pathname,
	t_data *data, t_cmd_node *cmd_node)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = cmd_node->cmd->cmd;
	errno = 0;
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
		else if (errno == EACCES)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			perror(cmd);
			data->exit_status = 126;
			return (1);
		}
		i++;
	}
	return (0);
}

int	find_path_with_access(char **paths, char **pathname,
	t_data *data, t_cmd_node *cmd_node)
{
	char	*cmd;

	cmd = cmd_node->cmd->cmd;
	if (!path_access_loop(paths, pathname, data, cmd_node))
	{
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		data->exit_status = 127;
	}
	return (0);
}

int	get_cmd_path_name(t_cmd_node *cmd_node, t_data *data)
{
	char	*pathname;
	char	*path;
	char	**paths;

	pathname = NULL;
	path = ft_getenv(data, "PATH");
	if (NULL == path)
	{
		msg_no_such_file_or_directory(data, 127, cmd_node->cmd->cmd);
		return (1);
	}
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
