/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:46:11 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/14 04:44:46 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_cmds(t_data *data)
{
	t_tokenlist	*current;
	t_tokenlist	*cmd_start;
	t_cmd_node	*new_node;
	t_tokenlist	*cmd_end;

	current = data->tokenlist;
	cmd_start = current;
	while (current)
	{
		cmd_end = NULL;
		if (current->type == TPIPE || current->next == NULL)
		{
			cmdlist_push_back(data, &data->cmd_node);
			new_node = cmdlist_getlast(data->cmd_node);
			if (current->type == TPIPE)
				cmd_end = current;
			extract_cmd_node(data, new_node, cmd_start, cmd_end);
			if (current->type == TPIPE)
				current = current->next;
			else if (current->next == NULL)
				current = NULL;
			cmd_start = current;
		}
		else
			current = current->next;
	}
}

t_tokenlist	*get_token(t_data *data, char *line, int *pos, t_tokenlist *tl)
{
	extract_space(data, tl, line, pos);
	if (!line[*pos])
		return (NULL);
	if (is_operator(&line[*pos]))
		return (extract_operator(data, tl, line, pos));
	if (line[*pos] == '"' || line[*pos] == '\'')
		return (extract_quotes(data, tl, line, pos));
	else
		return (extract_word(data, tl, line, pos));
}

void	set_token_type(t_data *data)
{
	set_file(data->tokenlist);
	set_cmds(data->tokenlist);
	set_builtin(data->tokenlist);
	set_limiter(data->tokenlist);
	set_args(data->tokenlist);
}

int	init_tokens(t_data *data)
{
	int			pos;
	t_tokenlist	*tmp;

	pos = 0;
	data->tokenlist = NULL;
	while (data->line[pos])
	{
		tmp = get_token(data, data->line, &pos, data->tokenlist);
		if (!tmp)
			break ;
		data->tokenlist = tmp;
	}
	find_expand(data);
	merge_token(&data->tokenlist);
	set_operator(data->tokenlist);
	if (is_invalid_redir(data->tokenlist))
		return (1);
	if (is_invalid_pipe(data->tokenlist))
		return (1);
	set_token_type(data);
	extract_cmds(data);
	return (0);
}
