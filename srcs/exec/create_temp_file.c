/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_temp_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:19:18 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/13 00:08:48 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

char	*add_random_alphanum(int fd, char *unique_id)
{
	int		read_random;
	char	buf;
	char	*new_str;

	read_random = 1;
	while (read_random <= 8)
	{
		if (read(fd, &buf, 1) < 1)
			return (NULL);
		if (ft_isalnum(buf))
		{
			new_str = ft_strjoin(unique_id, &buf);
			if (!new_str)
				free(unique_id);
			unique_id = new_str;
			free(new_str);
			read_random++;
		}
	}
}

char	*unique_id(char *unique_id)
{
    int 	fd;

	unique_id = NULL;
	fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
        return (NULL);
	unique_id = add_random_alphanum(fd, unique_id);
	close(fd);
	return (unique_id);
}

int	create_temp_file(t_filelist *cur_file_in)
{
	int		fd;
	char	*unique_id;

	unique_id = create_unique_id();
	if (!unique_id)
		return (-1);
    fd = open(cur_file_in->filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
        return (-1);

}
