/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/05 23:36:33 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_operator(char *line)
{
	if (!line)
		return (0);
	if (line[0] == '|')
		return (1);
	if (line[0] == '<')
	{
		if (line[1] == '<')
			return (2);
		return (1);
	}
	if (line[0] == '>')
	{
		if (line[1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

static int	is_builtin(char *word)
{
	const char	*builtin[8];
	int			i;

	i = 0;
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	while (builtin[i])
	{
		if (ft_strcmp(word, builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strndup(const char *src, int size)
{
	char	*dup;
	int		i;

	if (size == 0)
		return (NULL);
	i = 0;
	dup = (char *) malloc(sizeof(char) * size + 1);
	if (!dup)
		return (NULL);
	while (src[i] && i < size)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

void	set_operator(t_tokenlist *tl)
{
	t_tokenlist *current;

	current = tl;
	while(current)
	{
		if (current->type == TOPERATOR)
		{
			if (!current->token)
				return ;
			if (current->token[0] == '|')
				current->type = TPIPE;
			if (current->token[0] == '<')
			{
				if (current->token[1] == '<')
					current->type = THD;
				else
					current->type = TRD_IN;
			}
			if (current->token[0] == '>')
			{
				if (current->token[1] == '>')
					current->type = TAPPEND;
				else
					current->type = TRD_OUT;
			}
		}
		current = current->next;
	}
}

void	set_builtin(t_tokenlist *tl)
{
	t_tokenlist *current;

	current = tl;
	while(current)
	{
		if (current->type == TWORD)
		{
			if (!current->token)
				return ;
			if (is_builtin(current->token))
				current->type = TBUILTIN;
		}
		current = current->next;
	}
}

t_tokenlist *get_token(char	*line, int	*pos, t_tokenlist *tl)
{
	char	in_quote;
	int		start;
	int		len;
	
	in_quote = 0;
	start = *pos;
	len = 0;
	while (line[start] && ft_is_white_space(line[start]))
		start++;
	if (!line[start])
		return (NULL);
	if (is_operator(&line[start]))
	{
		len = is_operator(&line[start]);
		*pos = start + len;
		return (dlist_push_back(&tl, ft_strndup(&line[start], len), TOPERATOR));
	}
	if (line[start] == '"' || line[start] == '\'')
	{
		len = 1;
		in_quote = line[start];
		start++;
		if (line[start] == in_quote)
			return (tl);
		while (line[start + len] && line[start + len] != in_quote)
			len++;
		*pos = start + len + 1;
		if (in_quote == '"')
			return (dlist_push_back(&tl, ft_strndup(&line[start], len), TDQUOTES));
		else
			return (dlist_push_back(&tl, ft_strndup(&line[start], len), TQUOTES));
	}
	else
	{
		while (line[start + len] && !ft_is_white_space(line[start + len]) && line[start + len] != '"' && line[start + len] != '\'')
		{
			if (is_operator(&line[start + len]))
				break;
			len++;
		}
		*pos = start + len;
		return (dlist_push_back(&tl, ft_strndup(&line[start], len), TWORD));
	}
}

int	init_tokens(char *line)
{
	int		pos;
	t_tokenlist	*tl;
	t_tokenlist *tmp;
	
	pos = 0;
	tl = NULL;
	while (line[pos])
	{
		tmp = get_token(line, &pos, tl);
		if (!tmp)
			break;
		tl = tmp;
	}
	//print_dlist(tl, false);
	set_operator(tl);
	set_builtin(tl);
	print_dlist(tl, false);
	return (0);
}
