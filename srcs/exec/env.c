/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:45:06 by thibaud           #+#    #+#             */
/*   Updated: 2025/06/27 22:13:14 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	set_sh_lvl(t_data *data, char *str_sh_lvl)
{
	t_env_list	*cur_env_list;

	cur_env_list = data->env_list;
	while (cur_env_list)
	{
		if (ft_strcmp(cur_env_list->key, "SHLVL") == 0)
		{
			free(cur_env_list->value);
			cur_env_list->value = str_sh_lvl;
			return (1);
		}
		cur_env_list = cur_env_list->next;
	}
	return (1);
}

char	*ft_getenv(t_data *data, char *key)
{
	t_env_list	*cur_env_list;

	cur_env_list = data->env_list;
	while (cur_env_list)
	{
		if (ft_strcmp(cur_env_list->key, key) == 0)
			return (cur_env_list->value);
		cur_env_list = cur_env_list->next;
	}
	return (NULL);
}
