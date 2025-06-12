/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/11 21:08:18 by qutruche         ###   ########.fr       */
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

void	replace_token(t_tokenlist *token, t_env_list *env)
{
	int		len;
	char	*tmp;
	int		start;
	int		vlen;
	char	*new_token;
	char	*join;

	start = 0;
	len = 0;
	(void) env;
	(void)vlen;
	// printf("%zu - %d + %zu = %d\n", ft_strlen(token->token), varlen(var), ft_strlen(value), len);
	while (token->token[len] && token->token[len] != '$')
		len++;
	tmp = ft_substr(token->token, 0, (size_t)len);
	join = ft_strdup("");
	new_token = ft_strjoin(join, tmp);
	free(join);
	free(tmp);
	
	printf("REPLACE TOKEN [%s]\n", tmp);
	
	
}

void	find_expand(t_tokenlist *tl, t_env_list *env)
{
	t_tokenlist	*current;
	char		*expand;
	
	current = tl;
	while (current)
	{
		expand = ft_strchr(current->token, '$');
		if (expand)
		{
			printf("EXPAND : %s LEN :[%d] VALUE:[%s]\n", expand, \
			 varlen(expand), find_value(&expand[1],env));
			replace_token(tl, env);
		}	
		current = current->next;
	}
}