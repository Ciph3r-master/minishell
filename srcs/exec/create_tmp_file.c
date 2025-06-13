/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:19:18 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/13 02:30:32 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

char	*create_random_alphanum(int fd)
{
	int		read_random;
	char	buf;
	char	id[9];
	char	*random_alpha_num;

	read_random = 0;
	random_alpha_num = NULL;
	while (read_random < 8)
	{
		if (read(fd, &buf, 1) < 1)
			return (NULL);
		if (ft_is_id(buf))
		{
			id[read_random] = buf;
			read_random++;
		}
	}
	random_alpha_num = ft_strdup(id);
	if (!random_alpha_num)
		return (NULL);
	return (random_alpha_num);
}

char	*create_unique_id()
{
    int 	fd;
	char 	*unique_id;

	fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
		return (NULL);
	unique_id = create_random_alphanum(fd);
	if (!unique_id)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (unique_id);
}

char	*create_path_and_filename(t_filelist *cur_file_in)
{
	char	*unique_id;
	char	*new_filename;
	char	*path_and_filename;

	unique_id = create_unique_id();
	if (!unique_id)
		return (NULL);
	new_filename = ft_strjoin(cur_file_in->filename, unique_id);
	free(unique_id);
	if (!new_filename)
		return (NULL);
	new_filename = ft_strjoin(new_filename, ".tmp");
	if (!new_filename)
		return (NULL);
	cur_file_in->filename = new_filename;
	path_and_filename = ft_strjoin("./tmp/", cur_file_in->filename);
	if (!path_and_filename)
		return (NULL);
	return (path_and_filename);
}

// fonction de sortie free path and filename
//fonction de sortie free filename
int	create_tmp_file(t_filelist *cur_file_in)
{
	int		fd;
	char	*path_and_filename;

	fd = -1;
	while (fd == -1)
	{
		path_and_filename = create_path_and_filename(cur_file_in);
		if (!path_and_filename)
			return (-1);
		fd = open(path_and_filename, O_RDWR | O_CREAT | O_EXCL, 0644);
		if (fd != -1)
			cur_file_in->path_and_filename = path_and_filename;
	}
	return (fd);
}
