/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 03:57:40 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/11 22:39:17 by billcipher       ###   ########.fr       */
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

int builtin_export(t_cmd_node *cmd)
{
	char **args;

	args = cmd->cmd->args;
	//GERER MULTIARG
	if (!is_valid(args[1]))
	{
		print_export_err(args[1], "not a valid identifier");
		return (1);
	}
	return (0);
}
