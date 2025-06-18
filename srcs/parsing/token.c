/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/18 15:40:57 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	count_args(t_tokenlist *tl)
{
	t_tokenlist	*current;
	int			ac;

	ac = 0;
	current = tl;
	while (current && current->type != TPIPE)
	{
		if (current->type == TARG || current->type == TEXTERN || current->type == TBUILTIN)
			ac++;
		current = current->next;
	}
	printf("AC [%d]\n", ac);
	return (ac);
}

void	print_cmd(t_cmd *cmd)
{
	int i = 0;

	if (!cmd)
		return ;
	if (cmd->cmd)
		printf("Commande : %s\n", cmd->cmd);
	printf("Arguments :\n");
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			printf("  arg[%d] = [%s]\n", i, cmd->args[i]);
			i++;
		}
	}
	else
	{
		printf("  Aucun argument.\n");
	}

	if (cmd && cmd->pathname)
		printf("Chemin : %s\n", cmd->pathname);
}

//void	init_cmd_node(t_data *data)
//{
//	data->cmd_node = malloc(sizeof(t_cmd_node));
//	//TODO EXIT FREE
//	if (!data->cmd_node)
//		return ;
//	data->cmd_node->cmd = NULL;
//	data->cmd_node->file_in = NULL;
//	data->cmd_node->file_out = NULL;
//	data->cmd_node->fd_in = -1;
//	data->cmd_node->fd_out = -1;
//}

t_cmd *init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	//FREE AND EXIT
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->pathname = NULL;
	return (cmd);
}

void	init_args(t_tokenlist *start, t_cmd *cmd)
{
	char	**args;

	args = malloc(sizeof(char *) * (count_args(start) + 2));
	//FREE EXIT
	if (!args)
	{
		args = NULL;
		return ;
	}
	args[0] = NULL;
	cmd->args = args;
}

void extract_cmd_node(t_data *data, t_cmd_node *node, t_tokenlist *start, t_tokenlist *end)
{
	t_tokenlist	*current;
	t_tokenlist	*prev;
	int			ac;

	node->cmd = init_cmd();
	init_args(start, node->cmd);
	current = start;
	ac = 1;
	while (current && current != end)
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
			node->cmd->args[ac] = ft_strdup(current->token);
			ac++;
		}
		if (current->type == TLIMITER)
		{
			filelist_push_back(&node->file_in, ft_strdup("heredoc_"), FILE_HD);
			filelist_getlast(node->file_in)->limiter = ft_strdup(current->token);
			node->type |= HEREDOC;
		}
		if (current->type == TFILE)
		{
			prev = current->prev;
			if (current->prev && current->prev->type == TSPACE)
				prev = current->prev->prev;
			if (prev && prev->type == TRD_IN)
			{
				filelist_push_back(&node->file_in, ft_strdup(current->token), FILE_IN);
				node->type |= REDIRECT_IN;
			}
			if (prev && (prev->type == TRD_OUT || prev->type == TAPPEND))
			{
				if (prev->type == TRD_OUT)
				{
					filelist_push_back(&node->file_out, ft_strdup(current->token), FILE_OUT);
					node->type |= REDIRECT_OUT;
				}
				else
				{
					filelist_push_back(&node->file_out, ft_strdup(current->token), FILE_APPEND);
					node->type |= APPEND;
				}
			}
		}
		current = current->next;
	}
	if (count_args(start) != 0)
		data->cmd_node->cmd->args[ac] = NULL;
}

void	extract_cmds(t_data *data)
{
	t_tokenlist *current;
	t_tokenlist *cmd_start;
	t_cmd_node *new_node;
	t_tokenlist *cmd_end;

	current = data->tokenlist;
	cmd_start = current;
	while (current)
	{
		cmd_end = NULL;
		if (current->type == TPIPE || current->next == NULL)
		{
			cmdlist_push_back(&data->cmd_node);
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

t_tokenlist	*get_token(char	*line, int	*pos, t_tokenlist *tl)
{
	extract_space(tl, line, pos);
	if (!line[*pos])
		return (NULL);

	if (is_operator(&line[*pos]))
		return (extract_operator(tl, line, pos));
	if (line[*pos] == '"' || line[*pos] == '\'')
		return (extract_quotes(tl, line, pos));
	else
		return (extract_word(tl, line, pos));
}

int	init_tokens(t_data *data)
{
	int			pos;
	t_tokenlist	*tmp;

	pos = 0;
	data->tokenlist = NULL;
	while (data->line[pos])
	{
		tmp = get_token(data->line, &pos, data->tokenlist);
		if (!tmp)
			break ;
		data->tokenlist = tmp;
	}
	//print_dlist(tl, false);
	find_expand(&data->tokenlist, data->env_list);
	merge_token(&data->tokenlist);
	print_tokenlist(data->tokenlist, false);
	set_operator(data->tokenlist);
	set_cmds(data->tokenlist);
	set_builtin(data->tokenlist);
	set_file(data->tokenlist);
	set_limiter(data->tokenlist);

	set_args(data->tokenlist);
	print_tokenlist(data->tokenlist, false);
	extract_cmds(data);
	print_cmdlist(data->cmd_node);
	return (0);
}
