/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bill <bill@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:49:38 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/16 22:22:29 by bill             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	cmd_node_add_redir(t_data *data, t_cmd_node *node, t_tokenlist *current)
{
	t_tokenlist	*prev;

	prev = current->prev;
	if (prev->prev && prev->type == TSPACE)
		prev = prev->prev;
	if (prev && prev->type == TRD_IN)
	{
		filelist_push_back(data, &node->file_in, ft_strdup(current->token), FILE_IN);
		node->type |= REDIRECT_IN;
	}
	if (prev && (prev->type == TRD_OUT || prev->type == TAPPEND))
	{
		if (prev->type == TRD_OUT)
		{
			filelist_push_back(data, &node->file_out, ft_strdup(current->token), FILE_OUT);
			node->type |= REDIRECT_OUT;
		}
		else
		{
			filelist_push_back(data, &node->file_out, ft_strdup(current->token), FILE_APPEND);
			node->type |= APPEND;
		}
	}
}

void	cmd_node_set_cmd(t_tokenlist *current, t_cmd_node *node, int *ac)
{
	if (current->type == TEXTERN || current->type == TBUILTIN)
	{
		node->cmd->args[0] = ft_strdup(current->token);
		node->cmd->cmd = ft_strdup(current->token);
		if (current->type == TEXTERN)
			node->type |= EXTERN;
		else
			node->type |= BUILTIN;
	}
	if (current->type == TARG)
	{
		node->cmd->args[*ac] = ft_strdup(current->token);
		(*ac)++;
	}
}

void	cmd_node_set_hd(t_data *data, t_cmd_node *node, t_tokenlist *current)
{
	filelist_push_back(data, &node->file_in, ft_strdup("heredoc_"), FILE_HD);
	filelist_getlast(node->file_in)->limiter = ft_strdup(current->token);
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
		return ;
	}
	if (!init_args(start, node->cmd))
	{
		free_and_exit(data, 1);
	}
	current = start;
	ac = 1;
	while (current && current != end)
	{
		cmd_node_set_cmd(current, node, &ac);
		if (current->type == TLIMITER)
			cmd_node_set_hd(data, node, current);
		if (current->type == TFILE)
			cmd_node_add_redir(data, node, current);
		current = current->next;
	}
	node->cmd->args[ac] = NULL;
}
