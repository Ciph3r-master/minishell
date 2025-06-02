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

// exec :
// make libft
// cc execve.c ./../../libft/libft.a -I./../../includes/ -I./../../libft/

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

int	add_string_to_strings(char **strings, char *string)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (strings[i])
	{
		new_str = ft_strjoin(strings[i], string);
		if (new_str == NULL)
		{
			free_char_tab_all(strings);
			exit(1);
		}
		free(strings[i]);
		strings[i] = new_str;
		i++;
	}
	return (0);
}

// utilise les paths en boucle sur access pour voir si
// la commande entre par l'utilisateur correspond
// avec une commande qui existe dans les path
int	find_path_with_acces(char **paths, char *pathname)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (0 == access(paths[i], X_OK))
		{
			pathname = ft_strdup(paths[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

//utiliser access avec X_OK
// prend le PATH
// le split sur : avec split_set
// concatene la commande donne en argv avec les path
// "splitted_path"+"/cmd"
// parcour tous les split pour trouver si
// on a un path et un nom d'executable qui correspond a
// la commande donne en argv[1]
int	get_cmd_path_name(char *pathname, char **argv)
{
	char	*path;
	char	**paths;

	(void)pathname;
	(void)argv;
	path = getenv("PATH");
	if (NULL == path)
	{
		printf("getenv: can't get $PATH");
		exit(1);
	}
	paths = ft_split_set(path, ":");
	add_string_to_strings(paths, "/");
	add_string_to_strings(paths, argv[1]);
	if (1 == find_path_with_access(paths, pathname))
	{
		free_char_tab_all(paths);
		return (1);
	}
	free_char_tab_all(paths);
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

	pathname = NULL;
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
	printf("pathname : %s\n", pathname);



	// pid = fork();
	// loop = 1;
	// if (-1 == pid)
	// {
	// 	perror("fork");
	// 	return (0);
	// }
	// if (0 == pid)
	// {
	// 	while (loop)
	// 	{
	// 		if (-1 != execve(""))
	// 			loop = 0;
	// 	}
	// 	perror("execve");
	// 	exit(1);
	// }
	// else
	// {
	// 	wait(status);
	// 	printf("status : %s\n", status);
	// }
	return (0);
}
