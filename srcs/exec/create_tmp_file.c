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
	id[8] = '\0';
	random_alpha_num = ft_strdup(id);
	if (!random_alpha_num)
		return (NULL);
	return (random_alpha_num);
}

char	*create_unique_id(void)
{
	char	*unique_id;
	int		fd;

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

char	*create_pathname(t_filelist *cur_file_in, t_data *data)
{
	char	*unique_id;
	char	*new_filename;
	char	*pathname;

	if (!cur_file_in)
		free_and_exit(data, 1);
	unique_id = create_unique_id();
	if (!unique_id)
		free_and_exit(data, 1);
	new_filename = ft_strjoin(cur_file_in->filename, unique_id);
	free(unique_id);
	if (!new_filename)
		free_and_exit(data, 1);
	new_filename = ft_strjoin(new_filename, ".tmp");
	if (!new_filename)
		free_and_exit(data, 1);
	free(cur_file_in->filename);
	cur_file_in->filename = new_filename;
	pathname = ft_strjoin("/tmp/", cur_file_in->filename);
	if (!pathname)
		free_and_exit(data, 1);
	return (pathname);
}

int	create_tmp_file(t_filelist *cur_file_in, t_data *data)
{
	int		fd;
	char	*pathname;

	if (!cur_file_in)
		free_and_exit(data, 1);
	fd = -1;
	while (fd == -1)
	{
		pathname = create_pathname(cur_file_in, data);
		fd = open(pathname, O_RDWR | O_CREAT | O_EXCL, 0644);
		if (fd != -1)
			cur_file_in->pathname = pathname;
	}
	return (fd);
}
