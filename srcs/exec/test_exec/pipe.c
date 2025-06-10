/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 16:25:46 by thmaitre          #+#    #+#             */
/*   Updated: 2025-05-28 16:25:46 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fds[2];
	int		pid;
	char	read_from_child[24];

	if (-1 == pipe(fds))
	{
		perror("pipe");
		return (0);
	}
	pid = fork();
	if (-1 == pid)
	{
		perror("fork");
		return (0);
	}
	if (0 == pid)
	{
		close(fds[0]);
		write(fds[1], "bonjour depuis l'enfant\0", 24);
		close(fds[1]);
	}
	else
	{
		close(fds[1]);
		read(fds[0], read_from_child, 24);
		read_from_child[0] = 'C';
		printf("%s", read_from_child);
		close(fds[0]);
	}
	return (0);
}
