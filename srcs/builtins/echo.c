/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:27:33 by thibaud           #+#    #+#             */
/*   Updated: 2025/05/27 23:56:28 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	i = 0;
	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while ((u_s1[i] || u_s2[i]))
	{
		if (u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
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
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	return (0);
}

int	echo_simple(char **argv)
{
	int	i;

	i = 2;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}

int	builtin_echo(int argc, char **argv)
{
	if (argc == 1)
	{
		echo_no_args();
		return (0);
	}
	if (0 == ft_strcmp(argv[1], "-n"))
		echo_n_arg(argv);
	else
		echo_simple(argv);
	return (0);
}

int	main(int argc, char **argv)
{
	builtin_echo(argc, argv);
	return (0);
}
