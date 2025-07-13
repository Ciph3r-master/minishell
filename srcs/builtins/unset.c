/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 03:57:40 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/11 00:02:36 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	print_unset_err(char *arg, char *err_msg)
{
	const char	*prefix = "minishell: unset: `";

	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
}

static bool	is_valid(char *id)
{
	int	i;

	if (id[0] != '_' && !ft_isalpha(id[0]))
		return (false);
	i = 0;
	while (id[i])
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	remove_node(t_env_list **head, char *arg)
{
	t_env_list	*current;
	t_env_list	*prev;

	prev = NULL;
	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			if (!prev)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	// TODO A VOIR SI ON VEUT AFFICHER LE NOT FOUND (SUR POSIX JE L'AI PAS)
	print_unset_err(arg, "not found");
	return ;
}

int	builtin_unset(t_data *data, t_cmd_node *cmd_node)
{
	int		i;
	char	**args;

	i = 1;
	args = cmd_node->cmd->args;
	while (args[i])
	{
		if (!is_valid(args[i]))
		{
			print_unset_err(args[i], "is not a valid identifier");
			i++;
			continue ;
		}
		remove_node(&data->env_list, args[i]);
		i++;
	}
	return (0);
}
