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
#include "minishell.h"
#include "libft.h"

int	cmd_is_directory(t_cmd_node *cmd_node)
{
	(void)cmd_node;
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
