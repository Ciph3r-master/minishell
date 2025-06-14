/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/14 19:23:52 by qutruche         ###   ########.fr       */
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
		if (current->type == TARG)
			ac++;
		current = current->next;
	}
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
			printf("  arg[%d] = %s\n", i, cmd->args[i]);
			i++;
		}
	}
	else
	{
		printf("  Aucun argument.\n");
	}
}

void	create_cmd_node(t_tokenlist *tl, t_data *data)
{
	t_tokenlist	*current;
	t_cmd		*cmd;
	t_cmd_node	*node;
	t_filelist	*filein;
	t_filelist	*fileout;
	t_tokenlist	*prev;
	int			ac;
	char		**args;

	filein = NULL;
	fileout = NULL;
	node = malloc(sizeof(t_cmd_node));
	if (!node)
		return ;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	node->cmd = cmd;
	args = malloc(sizeof(char *) * (count_args(tl) + 2));
	if (!args)
		return ;
	ac = 1;
	current = tl;
	while (current && current->type != TPIPE)
	{
		if (current->type == TEXTERN || current->type == TBUILTIN)
		{
			args[0] = current->token;
			cmd->cmd = current->token;
		}
		if (current->type == TARG)
		{
			args[ac] = current->token;
			ac++;
		}	
		if (current->type == TLIMITER)
		{
			filelist_push_back(&filein, "tmp name", FILE_HD);
			filelist_getlast(filein)->limiter = current->token;
		}	
		if (current->type == TFILE)
		{
			prev = current->prev;
			if (current->prev && current->prev->type == TSPACE)
				prev = current->prev->prev;
			if (prev && prev->type == TRD_IN)
				filelist_push_back(&filein, current->token, FILE_IN);
			if (prev && (prev->type == TRD_OUT || prev->type == TAPPEND))
			{
				if (prev->type == TRD_OUT)
					filelist_push_back(&fileout, current->token, FILE_OUT);
				else
					filelist_push_back(&fileout, current->token, FILE_APPEND);
			}
		}
		current = current->next;
	}
	args[ac] = NULL;
	cmd->args = args;
	node->file_in = filein;
	node->file_out = fileout;
	// get_cmd_path_name(&cmd->path, cmd->cmd);
	printf("\nREDIRECTIONS\n");
	print_filelist(node->file_in, false);
	print_filelist(node->file_out, false);
	print_cmd(cmd);
	data->cmd_node = node;
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
	int		pos;
	t_tokenlist	*tl;
	t_tokenlist *tmp;

	pos = 0;
	tl = NULL;
	while (data->line[pos])
	{
		tmp = get_token(data->line, &pos, tl);
		if (!tmp)
			break ;
		tl = tmp;
	}
	//print_dlist(tl, false);
	find_expand(&tl, data->env_list);
	print_tokenlist(tl, false);
	set_operator(tl);
	set_builtin(tl);
	set_file(tl);
	set_limiter(tl);
	set_cmd(tl);
	set_args(tl);
	print_tokenlist(tl, false);
	create_cmd_node(tl, data);
	return (0);
}
