/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/13 15:59:26 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char *ft_strjoin3(char *s1, char *s2, char *s3)
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

int		varlen(char *var)
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

char	*find_value(char *var, t_env_list *envlist)
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

void	replace_token(t_tokenlist *token, t_env_list *env)
{
	int		start;
	int		len;
	char	*ntoken;
	char	*tmp;
	char	*join;
	int		pos;

	start = 0;
	len = 0;
	while (token->token && token->token[len] != '$')
		len++;
	ntoken = ft_substr(token->token, start, len);
	tmp = find_value(&token->token[len + 1], env);
	pos = len + varlen(&token->token[len + 1]) + 1;
	join = ft_strjoin3(ntoken, tmp, &token->token[pos]);
	token->token = join;
}

void	find_expand(t_tokenlist *tl, t_env_list *env)
{
	t_tokenlist	*current;
	char		*expand;

	current = tl;
	while (current)
	{
		expand = ft_strchr(current->token, '$');
		while (current->type != TQUOTES && expand)
		{
			printf("EXPAND : %s LEN :[%d] VALUE:[%s]\n", expand, \
			 varlen(expand), find_value(&expand[1], env));
			replace_token(current, env);
			expand = ft_strchr(current->token, '$');
		}
		current = current->next;
	}
}