/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_level.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:40:20 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/19 03:05:55 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	sh_level(t_data *data)
{
	char	*str_sh_lvl;
	int		sh_lvl;

	str_sh_lvl = NULL;
	if (isatty(STDIN_FILENO))
	{
		str_sh_lvl = ft_getenv(data, "SHLVL");
	}
	if (str_sh_lvl)
	{
		sh_lvl = ft_atoi(str_sh_lvl);
		sh_lvl++;
		str_sh_lvl = ft_itoa(sh_lvl);
		set_sh_lvl(data, str_sh_lvl);
	}
	return (1);
}
