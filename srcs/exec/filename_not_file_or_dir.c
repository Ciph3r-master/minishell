/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_not_file_or_dir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 03:24:55 by vscode            #+#    #+#             */
/*   Updated: 2025/07/14 02:31:53 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_filename(char *filename)
{
	if (ft_strcmp(".", filename) == 0)
		return (0);
	else if (ft_strcmp("..", filename) == 0)
		return (0);
	if (ft_strchr(filename, '/') != NULL)
		return (0);
	return (1);
}

int	pathname_len(char *last_slash, char *filename)
{
	int	path_len;

	path_len = 0;
	while (&filename[path_len] != last_slash)
		path_len++;
	return (path_len);
}

char	*copy_pathname(t_data *data, int path_len,
			char *filename, char *pathname)
{
	int	i;

	i = 0;
	pathname = malloc(sizeof(char) * (path_len + 2));
	if (!pathname)
		free_and_exit(data, 1);
	while (i <= path_len)
	{
		pathname[i] = filename[i];
		i++;
	}
	pathname[i] = filename[i];
	pathname[path_len + 1] = '\0';
	return (pathname);
}

int	extract_pathname(t_data *data, char *pathname, char *filename)
{
	char	*last_slash;
	int		path_len;

	(void)data;
	last_slash = ft_strrchr(filename, '/');
	path_len = pathname_len(last_slash, filename);
	pathname = copy_pathname(data, path_len, filename, pathname);
	printf("pathname :%s\n", pathname);
	return (1);
}

int	extract_filename(t_data *data, char *pathname, char *filename)
{
	char	*last_slash;
	int		path_len;

	(void)data;
	last_slash = ft_strrchr(filename, '/');
	path_len = pathname_len(last_slash, filename);
	pathname = copy_pathname(data, path_len, filename, pathname);
	printf("pathname :%s\n", pathname);
	return (1);
}

// on enleve le nom du fichier dans le filename donne
// on test le directory
// ../waefa/file.c
// je copie
// 0 on a un path ou un filname fonctionnel, 1 on a une erreur
int	filename_not_file_or_dir(t_data *data, t_filelist *cur_file_out)
{
	char	*filename;
	char	*pathname;

	(void)data;
	printf("filename :%s\n", cur_file_out->filename);
	filename = cur_file_out->filename;
	pathname = cur_file_out->pathname;
	if (is_filename(filename))
	{
		printf("is filename\n");
		return (0);
	}
	else
	{
		printf("is not filename\n");
	}
	if (ft_strchr(filename, '/') != NULL)
	{
		printf("il y a un /\n");
		extract_pathname(data, pathname, filename);
		extract_filename(data, pathname, filename);
	}
	return (1);
}
