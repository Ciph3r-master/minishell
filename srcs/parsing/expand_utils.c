/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:48:59 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/18 15:54:26 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
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

int	varlen(char *var)
{
	int	i;

	i = 1;
	if (!var[0] || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			break ;
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
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_prefix(t_data *data, t_tokenlist *token, int *len)
{
	char	*prefix;

	*len = 0;
	while (token->token && token->token[*len] != '$')
		(*len)++;
	prefix = ft_substr(token->token, 0, *len);
	if (!prefix)
		free_and_exit(data, 1);
	return (prefix);
}
