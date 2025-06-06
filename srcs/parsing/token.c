/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:49:40 by qutruche          #+#    #+#             */
/*   Updated: 2025/06/06 22:14:02 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	add_string_to_strings(char **strings, char *string)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (strings[i])
	{
		new_str = ft_strjoin(strings[i], string);
		if (new_str == NULL)
		{
			printf("strjoin: failed\n");
			free_char_tab_all(strings);
			exit(1);
		}
		free(strings[i]);
		strings[i] = new_str;
		i++;
	}
	return (0);
}

static int	check_path_with_access(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (0 == access(paths[i], X_OK))
			return (1);
		i++;
	}
	return (0);
}

int	find_path_with_access(char **paths, char **pathname)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (0 == access(paths[i], X_OK))
		{
			*pathname = ft_strdup(paths[i]);
			if (NULL == *pathname)
			{
				printf("ft_strdup: failed\n");
				free_char_tab_all(paths);
				exit (EXIT_FAILURE);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_command(char *word)
{
	char	*path;
	char	**paths;

	path = getenv("PATH");
	if (access(word, X_OK) == 0)
		return (1);
	if (NULL == path)
	{
		printf("getenv: can't get $PATH");
		exit(1);
	}
	paths = ft_split_set(path, ":");
	add_string_to_strings(paths, "/");
	add_string_to_strings(paths, word);
	if (0 == check_path_with_access(paths))
	{
		free_char_tab_all(paths);
		return (0);
	}
	free_char_tab_all(paths);
	return (1);
}

int	get_cmd_path_name(char **pathname, char *cmd)
{
	char	*path;
	char	**paths;

	if (access(cmd, X_OK) == 0)
	{
		*pathname = cmd;
		return (1);
	}
	path = getenv("PATH");
	if (NULL == path)
	{
		printf("getenv: can't get $PATH");
		exit(1);
	}
	paths = ft_split_set(path, ":");
	add_string_to_strings(paths, "/");
	add_string_to_strings(paths, cmd);
	if (0 == find_path_with_access(paths, pathname))
	{
		free_char_tab_all(paths);
		return (0);
	}
	free_char_tab_all(paths);
	return (1);
}

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
//TODO GERER AUSSI LES COMMANDES IN QUOTES arg ...
void	set_cmd(t_tokenlist *tl)
{
	t_tokenlist *current;

	current = tl;
	while(current)
	{
		if (current->type)
		{
			if (!current->token)
				return ;
			if (!is_builtin(current->token) && is_command(current->token))
				current->type = TEXTERN;
		}
		current = current->next;
	}
}

void	set_file(t_tokenlist *tl)
{
	t_tokenlist *current;
	t_tokentype	type;

	current = tl;
	while(current)
	{
		type = current->type;
		if (current->next != NULL && (type == TRD_IN || type == TRD_OUT || type == TAPPEND))
			current->next->type = TFILE;
		current = current->next;
	}
}

void	set_limiter(t_tokenlist *tl)
{
	t_tokenlist *current;
	t_tokentype	type;

	current = tl;
	while(current)
	{
		type = current->type;
		if (type == THD)
			current->next->type = TLIMITER;
		current = current->next;
	}
}

void	set_args(t_tokenlist *tl)
{
	t_tokenlist *current;
	t_tokentype	type;

	current = tl;
	while(current)
	{
		type = current->type;
		if (type == TWORD)
			current->type = TARG;
		if ((type == TEXTERN || type == TBUILTIN)
			&& current->next != NULL
			&& current->next->type != TRD_IN 
			&& current->next->type != TRD_OUT
			&& current->next->type != TRD_IN
			&& current->next->type != TAPPEND
			&& current->next->type != THD)
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

void print_cmd(t_cmd *cmd)
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

	printf("Chemin : %s\n", cmd->path);
}

void	*create_cmd_node(t_tokenlist *tl)
{
	t_tokenlist	*current;
	t_cmd		cmd;
	t_cmd_node	*node;
	int			ac;
	char		**args;

	node = malloc(sizeof(t_cmd_node));
	if (!node)
		return (NULL);
	node->cmd = &cmd;
	args = malloc(sizeof(char *) * (count_args(tl) + 2));
	if (!args)
		return (NULL);
	ac = 1;
	current = tl;
	while (current && current->type != TPIPE)
	{
		if (current->type == TEXTERN || current->type == TBUILTIN)
		{
			args[0] = current->token;
			cmd.cmd = current->token;
		}
		if (current->type == TARG)
		{
			args[ac] = current->token;
			ac++;
		}
		current = current->next;
	}
	args[ac] = NULL;
	cmd.args = args;
	get_cmd_path_name(&cmd.path, cmd.cmd);
	print_cmd(&cmd);
	return (node);
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
		{
			*pos = start + len;
			return (tl);
		}
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
	set_cmd(tl);
	set_file(tl);
	set_limiter(tl);
	set_args(tl);
	print_dlist(tl, false);
	//create_cmd_node(tl);
	return (0);
}
