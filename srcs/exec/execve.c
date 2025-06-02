/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 12:14:04 by thmaitre          #+#    #+#             */
/*   Updated: 2025-05-28 12:14:04 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	print_char_tab(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("argv[%d]:%s\n", i, argv[i]);
		i++;
	}
	return (0);
}

//utiliser access avec X_OK
// prend le PATH
// le split sur : avec split_set
// parcour tous les split pour trouver si
// on a un path et un nom d'executable qui correspond a
// la commande donne en argv[1]
int	get_cmd_path_name(char *pathname, char **argv)
{
	char	*path;

	(void)pathname;
	(void)argv;
	path = getenv("PATH");
	if (NULL == path)
	{
		printf("getenv: can't get $PATH");
		exit(1);
	}
	return (0);
}

//faire un programme avec execve qui cree un enfant
//execute et tue l'enfant
int	main(int argc, char **argv, char **env)
{
	int		pid;
	int		status;
	int		loop;
	char	*pathname;

	if (1 == argc || 3 < argc)
	{
		printf("Usage: use shell command with arg");
		exit(1);
	}
	if (1 == get_cmd_path_name(pathname, argv))
	{
		printf("Error: enter valid cmd");
		exit(1);
	}
	pid = fork();
	loop = 1;
	if (-1 == pid)
	{
		perror("fork");
		return (0);
	}
	if (0 == pid)
	{
		while (loop)
		{
			if (-1 != execve(""))
				loop = 0;
		}
		perror("execve");
		exit(1);
	}
	else
	{
		wait(status);
		printf("status : %s\n", status);
	}
	return (0);
}
