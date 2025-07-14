/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 03:57:40 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/14 04:40:11 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void print_export_err(char *arg, char *err_msg)
{
	const char *prefix = "minishell: export: `";

	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
}

static void add_var_to_env(t_data *data, char *arg)
{
	char		*value;
	char		*key;
	int			len;
	t_env_list	*new_node;

	value = ft_strchr(arg, '=') + 1;
	if (!value)
		return ;
	len = 0;
	while (value[len] && value[len] != '=')
		len++;
	key = ft_substr(arg, 0, len);
	if (!key)
		free_and_exit(data, 1);
	//SI NODE EXISTE DEJA JUSTE SET LA NOUVELLE KEY
	new_node = new_node_env_list(key, ft_strdup(value));
	if (!new_node)
	{
		free(key);
		free_and_exit(data, 1);
	}
	push_back_env_list(&data->env_list, new_node);
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

int builtin_export(t_data *data, t_cmd_node *cmd)
{
	char **args;

	args = cmd->cmd->args;
	//GERER MULTIARG
	if (!is_valid(args[1]))
	{
		print_export_err(args[1], "not a valid identifier");
		return (1);
	}
	add_var_to_env(data, args[1]);
	return (0);
}
