/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tmp_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:55:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/13 02:29:07 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

void delete_tmp_files(void)
{
    DIR				*dir;
    struct dirent	*entry;
    char			*path;

    dir = opendir("./tmp/");
    if (!dir)
        return;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' &&
           (entry->d_name[1] == '\0' ||
           (entry->d_name[1] == '.' && entry->d_name[2] == '\0')))
            continue;

        path = ft_strjoin("./tmp/", entry->d_name);
        if (!path)
            continue;
        unlink(path);
        free(path);
    }
    closedir(dir);
}
