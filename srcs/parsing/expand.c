/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/27 15:02:29 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		len1;
	int		len2;
	int		len3;
	char	*join;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	join = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, len1);
	ft_memcpy(join + len1, s2, len2);
	ft_memcpy(join + len1 + len2, s3, len3);
	join[len1 + len2 + len3] = 0;
	return (join);
}

static int	varlen(char *var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			break ;
		i++;
	}
	return (i);
}

static char	*find_value(char *var, t_env_list *envlist)
{
	int			var_len;
	t_env_list	*current;

	var_len = varlen(var);
	current = envlist;
	while (current)
	{
		if ((int)(ft_strlen(current->key)) == var_len
			&& ft_strncmp(var, current->key, (size_t)var_len) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static void	replace_token(t_data *data, t_tokenlist *token)
{
	int		start;
	int		len;
	char	*prefix;
	char	*tmp;
	char	*join;
	int		pos;

	start = 0;
	len = 0;
	while (token->token && token->token[len] != '$')
		len++;
	prefix = ft_substr(token->token, start, len);
	tmp = find_value(&token->token[len + 1], data->env_list);
	pos = len + varlen(&token->token[len + 1]) + 1;
	join = ft_strjoin3(prefix, tmp, &token->token[pos]);
	if (!join)
	{
		free(prefix);
		free_and_exit(data, 1);
	}
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
		tokenlist_insert_after(current, ft_strdup(split[i - 1]), TARG);
		if (i - 1 > 0)
			tokenlist_insert_after(current, NULL, TSPACE);
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
