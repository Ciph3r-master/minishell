/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:47:00 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/16 20:38:30 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

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
	exec_out = find_path_with_access(paths, &pathname) != 1;
	if (exec_out != 1)
	{
		ft_free_char_tab_all(paths);
		return (exec_out);
	}
	cmd_node->cmd->pathname = pathname;
	ft_free_char_tab_all(paths);
	return (1);
}

int exec_extern(t_cmd_node *cmd_node)
{
	int		exec_out;

	if (!cmd_node || !cmd_node->cmd->cmd)
		return (-1);
	exec_out = get_cmd_path_name(cmd_node);
	if (exec_out == -2)
	{
		//stderr
		printf("minishell: %s: command not found\n", cmd_node->cmd->cmd);
		return (exec_out);
	}
	return (1);
}

int	cmd_is_directory(t_cmd_node *cmd_node)
{
	return (1);
}

//on doit checker avant toute chose si la commande est un directory
// 1 la commande a ete execute avec succes
// -1 free and exit
// -2 la commande n'existe pas, est un directory, un file_in n'existe pas

//on a fait les redirection avec retour d'erreur -1 et -2
//on "sait" si ce n'est pas un directory avec erreur -1 et -2
//on doit maintenant trouver et executer la commande avec erreur -2
//	si n'existe pas et erreur -1 en cas de pb
int exec_simple_cmd_extern(t_cmd_node *cmd_node)
{
	int	exec_out;
	int saved_stdin;
	int saved_stdout;

	if (!cmd_node || !cmd_node->type)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (-1);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(saved_stdin);
		return (-1);
	}
	exec_out = exec_redirections(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	exec_out = cmd_is_directory(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	exec_out = exec_extern(cmd_node);
	if (exec_out != 1)
		return (exec_out);
	if (reset_stdin_stdout(saved_stdin, saved_stdout) != 1)
		return (-1);
	return (1);
}
