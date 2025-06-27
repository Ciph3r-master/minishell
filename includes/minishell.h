/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:45 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/27 02:41:46 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>

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
	char	*pathname;
}	t_cmd;

typedef struct s_filelist	t_filelist;

typedef struct s_filelist
{
	int					fd;
	char				*filename;
	char				*pathname;
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
	int			cmd_exit_status;
	t_filelist	*file_in;
	t_filelist	*file_out;
	t_cmd		*cmd;
	t_cmd_node	*prev;
	t_cmd_node	*next;
}	t_cmd_node;

typedef struct s_data
{
	int			old_pipe[2];
	int			new_pipe[2];
	int			saved_stdin;
	int			saved_stdout;
	int			exit_status;
	char		*pwd;
	char		*line;
	char		*old_pwd;
	char		**env_copy;
	t_tokenlist	*tokenlist;
	t_env_list	*env_list;
	t_cmd_node	*cmd_node;
}	t_data;

//	srcs/parsing/quotes.c
int			is_open_quotes(char *line, char quote);
t_tokenlist	*get_token(char	*line, int	*pos, t_tokenlist *tl);
int			init_tokens(t_data *data);

int			init_args(t_tokenlist *start, t_cmd *cmd);
t_cmd 		*init_cmd(void);

	// extract_token.c
	t_tokenlist *extract_word(t_tokenlist *tl, char *line, int *pos);
t_tokenlist	*extract_quotes(t_tokenlist *tl, char *line, int *pos);
t_tokenlist	*extract_operator(t_tokenlist *tl, char *line, int *pos);
t_tokenlist	*extract_space(t_tokenlist *tl, char *line, int *pos);
void extract_cmd_node(t_data *data, t_cmd_node *node, t_tokenlist *start, t_tokenlist *end);

void merge_token(t_tokenlist **tl);
// set_token_type.c
void 	set_operator(t_tokenlist *tl);
void	set_builtin(t_tokenlist *tl);
void	set_cmd(t_tokenlist *tl);
void	set_file(t_tokenlist *tl);
void	set_limiter(t_tokenlist *tl);
void	set_args(t_tokenlist *tl);
void 	set_cmds(t_tokenlist *tl);

// token utils
int 		is_builtin(char *word);
int			is_operator(char *line);
bool 		is_redirection(t_tokentype type);

//syntax_error.c
bool is_invalid_redir(t_tokenlist *tl);
bool is_invalid_pipe(t_tokenlist *tl);
	// DLIST
	t_tokenlist *tokenlist_create_node(void *content, t_tokentype type);
t_tokenlist	*tokenlist_push_front(t_tokenlist **tokenlist, void *content, t_tokentype type);
void		print_tokenlist(t_tokenlist *tokenlist, bool reverse);
t_tokenlist	*tokenlist_push_back(t_tokenlist **tokenlist, void *content, t_tokentype type);
t_tokenlist *tokenlist_insert_after(t_tokenlist *node, void *content, t_tokentype type);
void 		tokenlist_remove_node(t_tokenlist **head, t_tokenlist *node);
t_filelist *filelist_create_node(void *content, t_filetype type);
t_filelist	*filelist_push_front(t_filelist **filelist, void *content, t_filetype type);
void		print_filelist(t_filelist *filelist, bool reverse);
t_filelist	*filelist_push_back(t_filelist **filelist, void *content, t_filetype type);
t_filelist	*filelist_getlast(t_filelist *filelist);
t_cmd_node 	*cmdlist_create_node(void);
t_cmd_node 	*cmdlist_push_front(t_cmd_node **cmdlist);
t_cmd_node 	*cmdlist_push_back(t_cmd_node **cmdlist);
t_cmd_node 	*cmdlist_getlast(t_cmd_node *cmdlist);
void 		print_cmdlist(t_cmd_node *cmdlist);

// builtins/
	// pwd.c
int		builtin_pwd(void);

//expand
void	find_expand(t_tokenlist **tl, t_env_list *env);

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

// error/
	// free_and_exit.c
void		free_and_exit(t_data *data, int exit_code);

// exec/
	// builtins.c
int			exec_simple_cmd_builtins(t_cmd_node *cmd_node, t_data *data);
	// cmd_path.c
int			cmd_is_directory(t_cmd_node *cmd_node, t_data *data);
int			is_cmd_name_executable(t_cmd_node *cmd_node, t_data *data);
int			find_path_with_access(char **paths, char **pathname, t_data *data);
int			get_cmd_path_name(t_cmd_node *cmd_node, t_data *data);
	// create_tmp_file.c
int			create_tmp_file(t_filelist *cur_file_in, t_data *data);
	// exec_pipe.c
int			exec_pipe(t_cmd_node *cmd_node, t_data *data);
	// exec.c
int			exec(t_data *data);
int			exec_simple_cmd(t_cmd_node *cmd_node, t_data *data);
	// extern.c
int			exec_simple_cmd_extern(t_cmd_node *cmd_node, t_data *data);
	// faker_extern.c
t_data		*init_extern_simple_cmd(t_data *data);
t_data		*init_extern_cmd_redir_in(t_data *data);
t_data		*init_extern_cmd_multi_redir_in(t_data *data);
t_data		*init_extern_cmd_multi_redir_in_heredoc(t_data *data);
t_data		*init_extern_cmd_multi_redir_in_multi_heredoc(t_data *data);
t_data		*init_extern_cmd_multi_redir_in_multi_heredoc_redir_out(t_data *data);
t_data		*init_extern_cmd_multi_redir_in_multi_heredoc_multi_redir_out(t_data *data);
t_data		*init_extern_cmd_multi_redir_in_multi_heredoc_multi_redir_out_append(t_data *data);
	// faker_builtin.c
t_data		*init_builtin_simple_cmd(t_data *data);
t_data		*init_builtin_cmd_redir_in(t_data *data);
t_data		*init_builtin_cmd_multi_redir_in(t_data *data);
t_data		*init_builtin_cmd_multi_redir_in_heredoc(t_data *data);
t_data		*init_builtin_cmd_multi_redir_in_multi_heredoc(t_data *data);
t_data		*init_builtin_cmd_multi_redir_in_multi_heredoc_redir_out(t_data *data);
t_data		*init_builtin_cmd_multi_redir_in_multi_heredoc_multi_redir_out(t_data *data);
t_data		*init_builtin_cmd_multi_redir_in_multi_heredoc_multi_redir_out_append(t_data *data);
	// heredoc.c
int			exec_heredoc(t_cmd_node *cmd_node, t_data *data);
	// redir_in_and_hd.c
int			exec_redir_in_and_hd(t_filelist	*cur_file_in, t_data *data);
	// redir_out_and_append.c
int			exec_redir_out_and_append(t_filelist *file_in, t_data *data);
	// redirections.c
int			save_stdin_stdout(int *saved_stdin, int *saved_stdout);
int			reset_stdin_stdout(t_data *data);
int			exec_redirections(t_cmd_node *cmd_node, t_data *data);

// memory/
	// delete_tmp_file.c
void		delete_tmp_files(t_data *data);
	// free_all.c
void		free_all(t_data *data, int exit_code);
	// free_env_copy.c
void		free_env_copy(char **env_copy);
	// free_env_list.c
void		free_env_list(t_env_list *env_list);
	// free_pathname.c
void		free_pathname(t_filelist *cur_file_in);
	// free_tokens.c
void		free_tokenlist(t_tokenlist **tl);
	// free_cmd_node.c
void		free_cmd_list(t_cmd_node **cmd_node);
	//	free_utils.c
void		free_matrix(char **split);

// signals/
	// init_signals.c
void		init_signals(void);
void		sigint_handler(int sig);

#endif
