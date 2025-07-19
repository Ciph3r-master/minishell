/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:49:38 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/19 03:16:58 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	cmd_handle_redir_out(t_data *data, t_tokenlist *prev,
	t_cmd_node *node, t_tokenlist *current)
{
	if (prev && (prev->type == TRD_OUT || prev->type == TAPPEND))
	{
		if (prev->type == TRD_OUT)
		{
			filelist_push_back(data, &node->file_out,
				secure_strdup(data, current->token), FILE_OUT);
			node->type |= REDIRECT_OUT;
		}
		else
		{
			filelist_push_back(data, &node->file_out,
				secure_strdup(data, current->token), FILE_APPEND);
			node->type |= APPEND;
		}
	}
}

void	cmd_node_add_redir(t_data *data, t_cmd_node *node, t_tokenlist *current)
{
	t_tokenlist	*prev;

	prev = current->prev;
	if (prev->prev && prev->type == TSPACE)
		prev = prev->prev;
	if (prev && prev->type == TRD_IN)
	{
		filelist_push_back(data, &node->file_in,
			secure_strdup(data, current->token), FILE_IN);
		node->type |= REDIRECT_IN;
	}
	cmd_handle_redir_out(data, prev, node, current);
}

void	cmd_node_set_cmd(t_data *data, t_tokenlist *current,
		t_cmd_node *node, int *ac)
{
	if (current->type == TEXTERN || current->type == TBUILTIN)
	{
		node->cmd->args[0] = secure_strdup(data, current->token);
		node->cmd->cmd = secure_strdup(data, current->token);
		if (current->type == TEXTERN)
			node->type |= EXTERN;
		else
			node->type |= BUILTIN;
	}
	if (current->type == TARG)
	{
		node->cmd->args[*ac] = secure_strdup(data, current->token);
		(*ac)++;
	}
}

void	cmd_node_set_hd(t_data *data, t_cmd_node *node, t_tokenlist *current)
{
	filelist_push_back(data, &node->file_in,
		secure_strdup(data, "heredoc_"), FILE_HD);
	filelist_getlast(node->file_in)->limiter = secure_strdup(data,
		current->token);
	node->type |= HEREDOC;
}

void	extract_cmd_node(t_data *data, t_cmd_node *node,
	t_tokenlist *start, t_tokenlist *end)
{
	t_tokenlist	*current;
	int			ac;

	node->cmd = init_cmd();
	if (!node->cmd)
	{
		free_and_exit(data, 1);
	}
	if (!init_args(start, node->cmd))
	{
		free_and_exit(data, 1);
	}
	current = start;
	ac = 1;
	while (current && current != end)
	{
		cmd_node_set_cmd(data, current, node, &ac);
		if (current->type == TLIMITER)
			cmd_node_set_hd(data, node, current);
		if (current->type == TFILE)
			cmd_node_add_redir(data, node, current);
		current = current->next;
	}
	node->cmd->args[ac] = NULL;
}
