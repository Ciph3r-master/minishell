/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfl_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 05:10:20 by vscode            #+#    #+#             */
/*   Updated: 2025/07/18 21:42:14 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	get_pwd_key_value(t_data *data, char **key, char **value)
{
	*key = ft_strdup("PWD");
	if (!*key)
		free_and_exit(data, 1);
	*value = getcwd(NULL, 0);
	if (*value == NULL)
	{
		free(key);
		free_and_exit(data, 1);
	}
}

void	get_shlvl_key_value(t_data *data, char **key, char **value)
{
	*key = ft_strdup("SHLVL");
	if (!*key)
		free_and_exit(data, 1);
	*value = ft_strdup("0");
	if (*value == NULL)
	{
		free(key);
		free_and_exit(data, 1);
	}
}

t_env_list	*create_dfl_env_list(t_data *data)
{
	t_env_list	*new_node;
	char		*key;
	char		*value;

	key = NULL;
	value = NULL;
	get_pwd_key_value(data, &key, &value);
	new_node = new_node_env_list(data, key, value);
	if (!new_node)
		free_and_exit(data, 1);
	push_back_env_list(&data->env_list, new_node);
	get_shlvl_key_value(data, &key, &value);
	new_node = new_node_env_list(data, key, value);
	if (!new_node)
		free_and_exit(data, 1);
	push_back_env_list(&data->env_list, new_node);
	return (data->env_list);
}
