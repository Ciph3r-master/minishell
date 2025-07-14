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
	if (ft_strcmp("..", filename) == 0)
		return (0);
	if (ft_strchr(filename, '/') != NULL)
		return (0);
	return (1);
}

char	*extract_dir(char *filename)
{
	(void)filename;
	return (NULL);
}

// on enleve le nom du fichier dans le filename donne
// on test le directory
int	filename_not_file_or_dir(char *filename)
{
	// char	*filename_copy;
	// char	*dir;

	printf("filename :%s\n", filename);
	if (is_filename(filename))
		return (0);
	// filename_copy = ft_strdup(filename);
	// dir = extract_dir(filename);
	return (0);
}
