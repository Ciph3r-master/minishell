/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:27:33 by thibaud           #+#    #+#             */
/*   Updated: 2025/05/27 21:44:22 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	builtin_echo(argc, argv);
	return (0);
}

int	echo_no_args(void)
{
	write(1, "\n", 1);
	return (0);
}

int	echo_n_arg(char **argv)
{
	int	i;

	i = 2;
	while(argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
	}
	return (0);
}

int	builtin_echo(int argc, char **argv)
{
	if (argc == 1)
	{
		echo_no_args();
		return (0);
	}
	if (ft_strcmp(argv[1], "-n"))
		echo_n_arg(argv);
	else
		echo_simple(argv);
}
