/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-02 18:39:46 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-02 18:39:46 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	redirect_out(int fd, char *filename)
{
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	//securiser dup2
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		printf("Usage: ./a.out <filename>");
		exit(1);
	}
	redirect_in(fd, argv[1]);

	printf("hello\n");

	close(fd);
	return (0);
}
