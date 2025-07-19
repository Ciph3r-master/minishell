/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:55:25 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 04:32:20 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
