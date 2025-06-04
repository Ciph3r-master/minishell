/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:45 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/04 23:24:20 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>

enum e_type
{
	PIPE			= 1 << 0,
	REDIRECT_IN		= 1 << 1,
	REDIRECT_OUT	= 1 << 2,
	APPEND			= 1 << 3,
	HEREDOC			= 1 << 4,
	EXTERN			= 1 << 5,
	BUILTIN			= 1 << 6,
};

typedef enum e_tokentype
{
	TOPERATOR,
	TWORD,
	TDQUOTES,
	TQUOTES,
	TRD_IN,
	TRD_OUT,
	THD,
	TARG,
	TEXTERN,
	TBUILTIN
}	t_tokentype;

typedef struct s_tokenlist
{
	char				*token;
	t_tokentype			type;
	struct	s_tokenlist	*next;
	struct	s_tokenlist	*prev;
}	t_tokenlist;


typedef struct s_data
{
	char	**env;
	char	*pwd;
	char	*old_pwd;
}	t_data;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_cmd_node	t_cmd_node;

typedef struct s_cmd_node
{
	int			type;
	int			fd_in;
	int			fd_out;
	int			error_code;
	char		*filename_in;
	char		*filename_out;
	t_cmd		*cmd;
	t_cmd_node	*prev;
	t_cmd_node	*next;
}	t_cmd_node;

//	srcs/parsing/quotes.c
int	is_open_quotes(char *line, char quote);
t_tokenlist *get_token(char	*line, int	*pos, t_tokenlist *tl);
int init_tokens(char *line);

//DLIST
t_tokenlist	*dlist_create_node(void	*content, t_tokentype type);
t_tokenlist	*dlist_push_front(t_tokenlist **tokenlist, void *content, t_tokentype type);
void	print_dlist(t_tokenlist *tokenlist, bool reverse);
t_tokenlist	*dlist_push_back(t_tokenlist **tokenlist, void *content, t_tokentype type);
#endif
