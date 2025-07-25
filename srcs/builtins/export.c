/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 03:57:40 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/26 01:17:43 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static void	print_export_err(char *arg, char *err_msg)
{
	const char	*prefix = "minishell: export: `";

	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
}

static void	add_var_to_env(t_data *data, char *arg)
{
	char		*value;
	t_env_list	*node_to_replace;
	char		*key;

	value = ft_strchr(arg, '=');
	key = get_key(data, arg);
	if (!value)
	{
		if (!get_env_by_key(data, key))
			add_new_var(data, key, NULL, true);
		else
			free(key);
		return ;
	}
	value += 1;
	node_to_replace = get_env_by_key(data, key);
	if (node_to_replace)
	{
		free(node_to_replace->value);
		node_to_replace->value = secure_strdup(data, value);
		free(key);
		return ;
	}
	add_new_var(data, key, ft_strdup(value), false);
	return ;
}

static bool	is_valid(char *arg)
{
	int	i;

	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (false);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	print_export_env(t_data *data)
{
	int		i;
	char	**envcpy;
	char	*key;

	envcpy = get_env_copy(data->env_list);
	if (!envcpy)
		free_and_exit(data, 1);
	sort_env(data, envcpy);
	i = 0;
	while (envcpy[i])
	{
		key = get_key(data, envcpy[i]);
		if (!key)
		{
			free_env_copy(envcpy);
			free_and_exit(data, 1);
		}
		if (get_env_by_key(data, key)->value == NULL)
			printf("export %s\n", key);
		else
			printf("export %s=\"%s\"\n", key, ft_strchr(envcpy[i], '=') + 1);
		free(key);
		i++;
	}
	free_env_copy(envcpy);
}

int	builtin_export(t_data *data, t_cmd_node *cmd)
{
	char	**args;
	int		i;

	args = cmd->cmd->args;
	i = 1;
	if (!args[i])
	{
		print_export_env(data);
		return (0);
	}
	while (args[i])
	{
		if (!is_valid(args[i]))
		{
			print_export_err(args[i], "not a valid identifier");
			data->exit_status = 1;
		}
		else
			add_var_to_env(data, args[i]);
		i++;
	}
	update_env_cpy(data);
	return (data->exit_status);
}
