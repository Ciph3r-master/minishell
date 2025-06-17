/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:14:04 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/16 19:13:46 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// exec :
// make libft
// cc execve.c ./../../libft/libft.a -I./../../includes/ -I./../../libft/

//pas les permission retour erreur = 126
// fichier inexistant = 127

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
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
			printf("strjoin: failed\n");
			free_char_tab_all(strings);
			exit(1);
		}
		free(strings[i]);
		strings[i] = new_str;
		i++;
	}
	return (0);
}

int	find_path_with_access(char **paths, char **pathname)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (0 == access(paths[i], X_OK))
		{
			*pathname = ft_strdup(paths[i]);
			if (NULL == *pathname)
			{
				printf("ft_strdup: failed\n");
				free_char_tab_all(paths);
				exit (EXIT_FAILURE);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_cmd_path_name(char **pathname, char **argv)
{
	char	*path;
	char	**paths;

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

int	execute_cmd_in_child_process(char *pathname, char **argv, char **env)
{
	int		pid;
	int		status;

	pid = fork();
	if (-1 == pid)
	{
		perror("fork");
		return (0);
	}
	if (0 == pid)
	{
		if (-1 != execve(pathname, &argv[1], env))
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(&status);
		printf("Exit status : %d\n", WEXITSTATUS(status));
	}
	return (0);
}

// find input shell command in argv, and execute in child process
int	main(int argc, char **argv, char **env)
{
	char	*pathname;

	pathname = NULL;
	if (1 == argc || 3 < argc)
	{
		printf("Usage: use shell command with arg");
		exit(1);
	}
	if (1 == get_cmd_path_name(&pathname, argv))
	{
		printf("Error: enter valid cmd");
		exit(1);
	}
	printf("pathname:%s\n", pathname);
	execute_cmd_in_child_process(pathname, argv, env);
	free(pathname);
	return (0);
}
