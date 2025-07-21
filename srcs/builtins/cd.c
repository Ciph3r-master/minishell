/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:25:26 by thibaud           #+#    #+#             */
/*   Updated: 2025/07/21 03:49:31 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "minishell.h"
#include "libft.h"

static void	print_cd_err(char *err_msg)
{
	const char	*prefix = "minishell: cd: ";

	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
}

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

int	goto_dir(t_data *data, char *path)
{
	char		*old_pwd;
	t_env_list	*env_old_pwd;

	env_old_pwd = get_env_by_key(data, "OLDPWD");
	if (!env_old_pwd)
	{
		print_cd_err("OLDPWD not set");
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
			print_cd_err("HOME not set");
			data->exit_status = 1;
			return (1);
		}
		data->exit_status = goto_dir(data, home->value);
		return (0);
	}
	if (args[2])
	{
		print_cd_err("too many arguments");
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = goto_dir(data, args[1]);
	return (0);
}
