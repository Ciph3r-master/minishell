/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 12:27:34 by thmaitre          #+#    #+#             */
/*   Updated: 2025-05-28 12:27:34 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int	pid;

	pid = fork();
	if (-1 == pid)
	{
		perror("fork");
		return (0);
	}
	if (0 == pid)
	{
		sleep(15);
		write(1, "enfant\n", 7);
	}
	else
	{
		sleep(10);
		write(1, "parent\n", 7);
	}
	wait(NULL);
	return (0);
}
