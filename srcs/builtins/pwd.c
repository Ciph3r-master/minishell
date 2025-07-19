/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:55:25 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 05:09:03 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	builtin_pwd(t_data *data)
{
	char	*cwd;
	char	*err_msg;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		err_msg = ft_strjoin("pwd: error retrieving current directory: ",
				"getcwd: cannot access parent directories");
		if (!err_msg)
			free_and_exit(data, 1);
		perror(err_msg);
		free(err_msg);
		data->exit_status = 1;
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	data->exit_status = 0;
	return (0);
}
