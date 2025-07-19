/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:25:26 by thibaud           #+#    #+#             */
/*   Updated: 2025/07/19 02:21:06 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

int	builtin_cd(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (-1 == chdir(".."))
	{
		perror("cd");
	}
	builtin_pwd();
	return (0);
}

int	main(int argc, char **argv)
{
	builtin_cd(argc, argv);
	return (0);
}
