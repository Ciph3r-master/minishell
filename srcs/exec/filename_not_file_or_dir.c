/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_not_file_or_dir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 03:24:55 by vscode            #+#    #+#             */
/*   Updated: 2025/07/14 23:22:45 by vscode           ###   ########.fr       */
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

int	extract_pathname(t_data *data, char **pathname, char *filename)
{
	char	*last_slash;
	int		path_len;

	(void)data;
	last_slash = ft_strrchr(filename, '/');
	path_len = pathname_len(last_slash, filename);
	*pathname = copy_pathname(data, path_len, filename, *pathname);
	return (1);
}

int	is_valid_pathname(t_data *data, char *pathname, char *filename)
{
	if (access(pathname, F_OK) != 0)
	{
		msg_no_such_file_or_directory(data, 1, filename);
		return (0);
	}
	return (1);
}

int	is_filename_file_or_dir(t_data *data, t_filelist *cur_file_out)
{
	char	*filename;
	char	*pathname;

	filename = cur_file_out->filename;
	pathname = cur_file_out->pathname;
	if (is_filename(filename))
		return (1);
	if (ft_strcmp(".", filename) == 0 || ft_strcmp("..", filename) == 0)
	{

		return (0);
	}
	else if (ft_strcmp("..", filename) == 0)
		return (0);
	if (ft_strchr(filename, '/') != NULL)
	{
		extract_pathname(data, &pathname, filename);
		if (is_valid_pathname(data, pathname, filename))
			return (1);
	}
	return (0);
}
