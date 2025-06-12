/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/12 19:03:34 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

void	replace_token(t_tokenlist *token, t_env_list *env, int *pos)
{
	int		start;
	int		len;
	char	*ntoken;
	char	*tmp;
	char	*join;
	start = 0;
	len = 0;
	(void) pos;
	(void) env;
	while (token->token && token->token[len] != '$')
		len++;
	ntoken = ft_substr(token->token, start, len);
	printf("NTOKEN : %s\n", ntoken);
	tmp = find_value(&token->token[len + 1], env);
	printf("TMP : %s\n", tmp);
	join = ft_strjoin(ntoken, tmp);
	printf("JOIN: %s\n", join);
	*pos = len + varlen(&token->token[len + 1]) + 1;
	printf("POS: %s\n", &token->token[*pos]);
	token->token = join;
}

void	find_expand(t_tokenlist *tl, t_env_list *env)
{
	t_tokenlist	*current;
	char		*expand;
	int			pos;

	pos = 0;
	current = tl;
	while (current)
	{
		expand = ft_strchr(&current->token[pos], '$');
		while (expand)
		{
			printf("EXPAND : %s LEN :[%d] VALUE:[%s]\n", expand, \
			 varlen(expand), find_value(&expand[1],env));
			replace_token(current, env, &pos);
			printf("coucou = %s\n", &current->token[pos]);
			expand = ft_strchr(&current->token[pos], '$');
		}
		current = current->next;
	}
}