/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:27:33 by thibaud           #+#    #+#             */
/*   Updated: 2025/07/19 02:13:58 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	check_option(char *arg)
{
	int	i;

	if (!arg || *arg != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	get_start(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_option(args[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

void	echo_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i] && args[i + 1])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (start == 0)
		printf("%s\n", args[i]);
	else if (args[i])
		printf("%s", args[i]);
}

int	builtin_echo(t_cmd_node *cmd_node)
{
	int	ac;

	ac = 0;
	while (cmd_node->cmd->args && cmd_node->cmd->args[ac + 1])
		ac++;
	if (ac == 0)
	{
		printf("\n");
		return (0);
	}
	echo_args(&cmd_node->cmd->args[1], get_start(&cmd_node->cmd->args[1]));
	return (0);
}
