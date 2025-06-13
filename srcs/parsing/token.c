/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/13 15:57:43 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// static int	add_string_to_strings(char **strings, char *string)
// {
// 	int		i;
// 	char	*new_str;

// 	i = 0;
// 	new_str = NULL;
// 	while (strings[i])
// 	{
// 		new_str = ft_strjoin(strings[i], string);
// 		if (new_str == NULL)
// 		{
// 			printf("strjoin: failed\n");
// 			free_char_tab_all(strings);
// 			exit(1);
// 		}
// 		free(strings[i]);
// 		strings[i] = new_str;
// 		i++;
// 	}
// 	return (0);
// }

// static int	check_path_with_access(char **paths)
// {
// 	int	i;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		if (0 == access(paths[i], X_OK))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
// int	get_cmd_path_name(char **pathname, char *cmd)
// {
// 	char	*path;
// 	char	**paths;

// 	if (access(cmd, X_OK) == 0)
// 	{
// 		*pathname = cmd;
// 		return (1);
// 	}
// 	path = getenv("PATH");
// 	if (NULL == path)
// 	{
// 		printf("getenv: can't get $PATH");
// 		exit(1);
// 	}
// 	paths = ft_split_set(path, ":");
// 	add_string_to_strings(paths, "/");
// 	add_string_to_strings(paths, cmd);
// 	if (find_path_with_access(paths, pathname) == 0)
// 	{
// 		free_char_tab_all(paths);
// 		return (0);
// 	}
// 	free_char_tab_all(paths);
// 	return (1);
// }

// int	find_path_with_access(char **paths, char **pathname)
// {
// 	int	i;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		if (access(paths[i], X_OK) == 0)
// 		{
// 			*pathname = ft_strdup(paths[i]);
// 			if (NULL == *pathname)
// 			{
// 				printf("ft_strdup: failed\n");
// 				free_char_tab_all(paths);
// 				exit (EXIT_FAILURE);
// 			}
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static	char	*ft_strndup(const char *src, int size)
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
	t_tokenlist	*current;

	current = tl;
	while (current)
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
	t_tokenlist	*current;

	current = tl;
	while (current)
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
//TODO GERER AUSSI LES COMMANDES IN QUOTES arg ...
void	set_cmd(t_tokenlist *tl)
{
	t_tokenlist	*current;

	current = tl;
	while (current)
	{
		if (current->type == TRD_IN
		|| current->type == TRD_OUT
		|| current->type == TAPPEND
		|| current->type == THD
		|| current->type == TFILE
		|| current->type == TLIMITER
		|| current->type == TSPACE
		|| current->type == TPIPE)
		{
			current = current->next;
			continue;
		}
		current->type = TEXTERN;
		break;
	}
}

void	set_file(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokentype	type;

	current = tl;
	while (current)
	{
		type = current->type;
		if (current->next != NULL
			&& current->next->type != TRD_IN
			&& current->next->type != TAPPEND
			&& current->next->type != TRD_OUT
			&& current->next->type != THD
			&& (type == TRD_IN || type == TRD_OUT || type == TAPPEND))
		{
			if (current->next && current->next->type == TSPACE)
				current = current->next;
			if (current->next)
				current->next->type = TFILE;
		}
		current = current->next;
	}
}

void	set_limiter(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokentype	type;

	current = tl;
	while(current)
	{
		type = current->type;
		if (type == THD 
			&& current->next != NULL)
		{
			if (current->next->type == TSPACE)
				current = current->next;
			current->next->type = TLIMITER;
		}
		current = current->next;
	}
}

void	set_args(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_tokentype	type;

	current = tl;
	while (current)
	{
		type = current->type;
		if (type == TWORD || type == TDQUOTES || type == TQUOTES)
			current->type = TARG;
		if ((type == TEXTERN || type == TBUILTIN)
			&& current->next != NULL
			&& current->next->type != TRD_IN
			&& current->next->type != TRD_OUT
			&& current->next->type != TRD_IN
			&& current->next->type != TAPPEND
			&& current->next->type != THD
			&& current->next->type != TPIPE
			&& current->next->type != TSPACE)
			current->next->type = TARG;
		current = current->next;
	}
}

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

	if (cmd && cmd->path)
		printf("Chemin : %s\n", cmd->path);
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

static	t_tokenlist	*extract_space(t_tokenlist *tl, char *line, int *pos)
{
	int			len;

	len = 0;
	while (line[*pos + len] && ft_is_white_space(line[*pos + len]))
		len++;
	*pos += len;
	if (len > 0)
		return (tokenlist_push_back(&tl, ft_strndup("", 1), TSPACE));
	return (tl);
}

static	t_tokenlist	*extract_operator(t_tokenlist *tl, char *line, int *pos)
{
	int			len;
	t_tokenlist	*ntl;

	len = is_operator(&line[*pos]);
	ntl = tokenlist_push_back(&tl, ft_strndup(&line[*pos], len), TOPERATOR);
	*pos += len;
	return (ntl);
}

static	t_tokenlist	*extract_quotes(t_tokenlist *tl, char *line, int *pos)
{
	int		len;
	char	in_quote;
	int		start;

	len = 1;
	in_quote = line[*pos];
	(*pos)++;
	start = *pos;
	if (line[start] == in_quote)
	{
		(*pos)++;
		return (tokenlist_push_back(&tl, ft_strndup("", 1), TDQUOTES));
	}
	while (line[start + len] && line[start + len] != in_quote)
		len++;
	*pos = start + len + 1;
	if (in_quote == '"')
		return (tokenlist_push_back(&tl, ft_strndup(&line[start], len), TDQUOTES));
	else
		return (tokenlist_push_back(&tl, ft_strndup(&line[start], len), TQUOTES));
}

static	t_tokenlist	*extract_word(t_tokenlist *tl, char *line, int *pos)
{
	int	start;
	int	len;

	start = *pos;
	len = 0;
	while (line[start + len]
		&& !ft_is_white_space(line[start + len])
		&& line[start + len] != '"' && line[start + len] != '\'')
	{
		if (is_operator(&line[start + len]))
			break ;
		len++;
	}
	*pos = start + len;
	return (tokenlist_push_back(&tl, ft_strndup(&line[start], len), TWORD));
}

t_tokenlist	*get_token(char	*line, int	*pos, t_tokenlist *tl)
{
	// if (ft_is_white_space(line[*pos]))
	// 	tokenlist_push_back(&tl, ft_strndup("", 1), TSPACE);
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
	find_expand(tl, data->env_list);
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
