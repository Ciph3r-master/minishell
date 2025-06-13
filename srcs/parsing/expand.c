/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:37 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/13 01:22:39 by thibaud          ###   ########.fr       */
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
	// int		start;
	int		len;

	// start = 0;
	len = 0;
	(void) env;
	while (token->token && token->token[len] != '$')
		len++;

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
