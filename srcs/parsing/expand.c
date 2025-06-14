/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/14 19:30:41 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char *ft_strjoin3(char *s1, char *s2, char *s3)
{
	int len1;
	int len2;
	int len3;
	char *join;

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

static int		varlen(char *var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			break;
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
		{
			printf("VARLEN : %d | KEYLEN %zu\n", var_len, ft_strlen(current->key));
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

static void	replace_token(t_tokenlist *token, t_env_list *env)
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
	tmp = find_value(&token->token[len + 1], env);
	pos = len + varlen(&token->token[len + 1]) + 1;
	join = ft_strjoin3(prefix, tmp, &token->token[pos]);
	token->token = join;
	free(prefix);
}

void	find_expand(t_tokenlist **tl, t_env_list *env)
{
	t_tokenlist	*current;
	t_tokenlist *tmp;
	char		*expand;
	char		**split_token;

	current = *tl;
	while (current)
	{
		if (!current->token)
		{
			current = current->next;
			continue;
		}
		expand = ft_strchr(current->token, '$');
		while (current->type != TQUOTES && expand)
		{
			printf("EXPAND : %s LEN :[%d] VALUE:[%s]\n", expand, \
			 varlen(expand), find_value(&expand[1], env));
			replace_token(current, env);
			expand = ft_strchr(current->token, '$');
		}
		if (current->type == TWORD)
		{
			split_token = ft_split(current->token);
			int i = 0;
			while (split_token[i])
				i++;
			i--;
			tmp = current->next;
			while (i >= 0)
			{
				tokenlist_insert_after(current, split_token[i], TARG);
				if (i > 0)
					tokenlist_insert_after(current, NULL, TSPACE);
				i--;
			}
			tokenlist_remove_node(tl, current);
			current = tmp;
		}
		else
			current = current->next;
	}
}
