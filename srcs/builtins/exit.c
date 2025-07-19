/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 03:57:40 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/18 20:22:52 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	print_exit_err(char *arg, char *err_msg)
{
	const char	*prefix = "minishell: exit: ";

	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
}

unsigned char	get_exit_code(char *arg, int *err)
{
	int					i;
	int					sign;
	long long			res;

	i = 0;
	res = 0;
	sign = 1;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		sign = 1 - 2 * (arg[i++] == '-');
	if ((arg[i] == '+' || arg[i] == '-') || (arg[i] < '0' || arg[i] > '9'))
		*err = -1;
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		res *= 10;
		res += arg[i++] - '0';
		if (((unsigned long int)res > LONG_MAX && sign == 1)
			|| ((unsigned long int)res > ((unsigned long int)LONG_MAX) + 1
				&& sign == -1))
			*err = -1;
	}
	if (arg[i])
		*err = -1;
	return ((unsigned char)(res * sign));
}

int	builtin_exit(t_data *data, t_cmd_node *cmd_node)
{
	char			**args;
	int				err;
	unsigned char	error_code;

	err = 0;
	args = cmd_node->cmd->args;
	printf("exit\n");
	if (!args[1])
		free_and_exit(data, data->prev_exit_status);
	error_code = get_exit_code(args[1], &err);
	if (err == -1)
	{
		print_exit_err(args[1], "numeric argument required");
		free_and_exit(data, 2);
	}
	if (args[2])
	{
		print_exit_err(NULL, "too many arguments");
		data->exit_status = 1;
		return (1);
	}
	free_and_exit(data, error_code);
	return (0);
}
