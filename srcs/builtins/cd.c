/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:25:26 by thibaud           #+#    #+#             */
/*   Updated: 2025/07/19 04:23:37 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include <errno.h>

int	goto_path(t_data *data, char *path)
{
	char	*err_prefix;

	if (chdir(path) == -1)
	{
		err_prefix = ft_strjoin("minishell: cd: ", path);
		if (!err_prefix)
			free_and_exit(data, 1);
		perror(err_prefix);
		free(err_prefix);
		return (-1);
	}
	return (0);
}

int goto_dir(t_data *data, char *path)
{
	char		*old_pwd;
	t_env_list	*env_old_pwd;

	env_old_pwd = get_env_by_key(data, "OLDPWD");
	if (!env_old_pwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (goto_path(data, path) == -1)
	{
		free(old_pwd);
		return (1);
	}
	free(env_old_pwd->value);
	env_old_pwd->value = old_pwd;
	free(get_env_by_key(data, "PWD")->value);
	get_env_by_key(data, "PWD")->value = getcwd(NULL, 0);
	free_env_copy(data->env_copy);
	data->env_copy = get_env_copy(data->env_list);
	return (0);
}

// cd sans arg : bash: cd: HOME not set ERROR CODE 1
// cd - : 
int	builtin_cd(t_data *data, t_cmd_node *cmd_node)
{
	char		**args;
	t_env_list	*home;

	args = cmd_node->cmd->args;
	if (!args[1])
	{
		home = get_env_by_key(data, "HOME");
		if (!home || !home->value)
		{
			//TODO UTILISER SORTIE ERR
			printf("minishell: cd: HOME not set\n");
			data->exit_status = 1;
			return (1);
		}
		data->exit_status = goto_dir(data, home->value);
		return (0);
	}
	if (args[2])
	{
		printf("minishell: cd: too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = goto_dir(data, args[1]);
	return (0);
}

