/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:45 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/12 18:16:11 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

typedef enum e_cmdtype
{
	PIPE			= 1 << 0,
	REDIRECT_IN		= 1 << 1,
	HEREDOC			= 1 << 2,
	REDIRECT_OUT	= 1 << 3,
	APPEND			= 1 << 4,
	EXTERN			= 1 << 5,
	BUILTIN			= 1 << 6,
}	t_cmdtype;

typedef enum e_tokentype
{
	TOPERATOR,
	TWORD,
	TDQUOTES,
	TQUOTES,
	TRD_IN,
	TRD_OUT,
	TPIPE,
	TAPPEND,
	THD,
	TFILE,
	TSPACE,
	TARG,
	TEXTERN,
	TLIMITER,
	TBUILTIN
}	t_tokentype;

typedef enum e_filetype
{
	FILE_IN,
	FILE_OUT,
	FILE_APPEND,
	FILE_HD
}	t_filetype;

typedef struct s_tokenlist
{
	char				*token;
	t_tokentype			type;
	struct s_tokenlist	*next;
	struct s_tokenlist	*prev;
}	t_tokenlist;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_filelist	t_filelist;

typedef struct s_filelist
{
	int					fd;
	char				*filename;
	char				*limiter;
	t_filetype			type;
	t_filelist			*next;
	t_filelist			*prev;
}	t_filelist;

typedef struct s_env_list	t_env_list;

typedef struct s_env_list
{
	char		*key;
	char		*value;
	t_env_list	*next;
}	t_env_list;

typedef struct s_cmd_node	t_cmd_node;

typedef struct s_cmd_node
{
	int			type;
	int			fd_in;
	int			fd_out;
	int			error_code;
	t_filelist	*file_in;
	t_filelist	*file_out;
	char		*delimiter;
	t_cmd		*cmd;
	t_cmd_node	*prev;
	t_cmd_node	*next;
}	t_cmd_node;

typedef struct s_data
{
	char		*pwd;
	char		*line;
	char		*old_pwd;
	char		**env_copy;
	t_env_list	*env_list;
	t_cmd_node	*cmd_node;
}	t_data;

//	srcs/parsing/quotes.c
int			is_open_quotes(char *line, char quote);
t_tokenlist	*get_token(char	*line, int	*pos, t_tokenlist *tl);
int			init_tokens(t_data *data);

//token utils
int			is_builtin(char *word);
int			is_operator(char *line);
//DLIST
t_tokenlist	*tokenlist_create_node(void	*content, t_tokentype type);
t_tokenlist	*tokenlist_push_front(t_tokenlist **tokenlist, void *content, t_tokentype type);
void		print_tokenlist(t_tokenlist *tokenlist, bool reverse);
t_tokenlist	*tokenlist_push_back(t_tokenlist **tokenlist, void *content, t_tokentype type);

t_filelist	*filelist_create_node(void	*content, t_filetype type);
t_filelist	*filelist_push_front(t_filelist **filelist, void *content, t_filetype type);
void		print_filelist(t_filelist *filelist, bool reverse);
t_filelist	*filelist_push_back(t_filelist **filelist, void *content, t_filetype type);
t_filelist	*filelist_getlast(t_filelist *filelist);

//expand
void	find_expand(t_tokenlist *tl, t_env_list *env);

// data/
	//init_data.c
int			init_data(t_data *data, char **env);

// env_copy/
	// env_list.c
t_env_list	*new_node_env_list(char *key, char *value);
void		push_back_env_list(t_env_list **env_list, t_env_list *new_node);
void		print_env_list(t_env_list **env_list);
int			get_env_list_size(t_env_list *env_list);
	// get_env_list.c
char		*get_env_key(char *env_line);
char		*get_env_value(char *env_line);
t_env_list	*get_env_list(t_data *data, char **env);
	// get_env_copy.c
char		**get_env_copy(t_env_list *env_list);
void		print_env_copy(char **env_copy);

// error
void		free_and_exit(t_data *data);

// exec
int			exec(t_data *data);

// memory/
void		free_all(t_data *data);
void		free_env_list(t_env_list *env_list);
void		free_env_copy(char **env_copy);

// signals/
void		init_signals(void);

#endif
