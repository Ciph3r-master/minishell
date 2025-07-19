/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/07/19 03:17:45 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	handle_value(t_data *data, char **tmp,
	t_tokenlist *token, int len)
{
	if (token->token[len + 1] == '?')
	{
		*tmp = ft_itoa(data->exit_status);
		return (len + 2);
	}
	else
	{
		*tmp = find_value(&token->token[len + 1], data->env_list);
		return (len + varlen(&token->token[len + 1]) + 1);
	}
}

static void	replace_token(t_data *data, t_tokenlist *token)
{
	char	*prefix;
	char	*tmp;
	char	*join;
	int		len;
	int		pos;

	prefix = get_prefix(data, token, &len);
	pos = handle_value(data, &tmp, token, len);
	join = ft_strjoin3(prefix, tmp, &token->token[pos]);
	if (!join)
	{
		free(prefix);
		if (token->token[len + 1] == '?')
			free(tmp);
		free_and_exit(data, 1);
	}
	if (token->token[len + 1] == '?')
		free(tmp);
	free(token->token);
	token->token = join;
	free(prefix);
}

static void	expand(t_data *data, t_tokenlist *current)
{
	char		*expand;

	expand = ft_strchr(current->token, '$');
	while (current->type != TQUOTES && expand)
	{
		replace_token(data, current);
		expand = ft_strchr(current->token, '$');
	}
}

static void	split_token(t_data *data, t_tokenlist *current)
{
	char		**split;
	int			i;

	split = ft_split(current->token);
	if (!split)
		free_and_exit(data, 1);
	i = 0;
	while (split[i])
		i++;
	while (i - 1 >= 0)
	{
		tokenlist_insert_after(data, current, secure_strdup(data,
				split[i - 1]), TARG);
		if (i - 1 > 0)
			tokenlist_insert_after(data, current, NULL, TSPACE);
		i--;
	}
	free_matrix(split);
	tokenlist_remove_node(&data->tokenlist, current);
}

void	find_expand(t_data *data)
{
	t_tokenlist	*current;
	t_tokenlist	*next;

	current = data->tokenlist;
	while (current)
	{
		if (!current->token)
		{
			current = current->next;
			continue ;
		}
		expand(data, current);
		if (current->type == TWORD)
		{
			next = current->next;
			split_token(data, current);
			current = next;
		}
		else
			current = current->next;
	}
}
