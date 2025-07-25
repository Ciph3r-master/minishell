/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:45 by thmaitre          #+#    #+#             */
/*   Updated: 2025/07/25 22:30:33 by billcipher       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <signal.h>

extern sig_atomic_t	g_exit_status;

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
	TBUILTIN,
	TUNKNOWN
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

typedef struct s_filelist
{
	int					fd;
	char				*filename;
	char				*pathname;
	char				*limiter;
	t_filetype			type;
	struct s_filelist	*next;
	struct s_filelist	*prev;
}	t_filelist;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_cmd_node
{
	int					type;
	int					fd_in;
	int					fd_out;
	int					cmd_exit_status;
	t_filelist			*file_in;
	t_filelist			*file_out;
	t_cmd				*cmd;
	struct s_cmd_node	*prev;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_data
{
	int			old_pipe[2];
	int			new_pipe[2];
	int			saved_stdin;
	int			saved_stdout;
	int			exit_status;
	int			prev_exit_status;
	int			exec_heredoc;
	int			pipe_signal;
	char		*pwd;
	char		*line;
	char		*old_pwd;
	char		**env_copy;
	t_tokenlist	*tokenlist;
	t_env_list	*env_list;
	t_cmd_node	*cmd_node;
}	t_data;

//	srcs/parsing/quotes.c
t_tokenlist	*get_token(t_data *data, char *line, int *pos, t_tokenlist *tl);
int			init_tokens(t_data *data);

int			init_args(t_tokenlist *start, t_cmd *cmd);
t_cmd		*init_cmd(void);

	// extract_token.c
t_tokenlist	*extract_word(t_data *data, t_tokenlist *tl, char *line, int *pos);
t_tokenlist	*extract_quotes(t_data *data, t_tokenlist *tl,
				char *line, int *pos);
t_tokenlist	*extract_operator(t_data *data, t_tokenlist *tl,
				char *line, int *pos);
t_tokenlist	*extract_space(t_data *data, t_tokenlist *tl,
				char *line, int *pos);
void		extract_cmd_node(t_data *data, t_cmd_node *node,
				t_tokenlist *start, t_tokenlist *end);
void		merge_token(t_data *data, t_tokenlist **tl);

// set_token_type.c
void		set_operator(t_tokenlist *tl);
void		set_builtin(t_tokenlist *tl);
void		set_cmd(t_tokenlist *tl);
void		set_file(t_tokenlist *tl);
void		set_limiter(t_tokenlist *tl);
void		set_args(t_tokenlist *tl);
void		set_cmds(t_tokenlist *tl);

// token utils
int			is_builtin(char *word);
int			is_operator(char *line);
bool		is_redirection(t_tokentype type);

//syntax_error.c
bool		is_invalid_redir(t_tokenlist *tl);
bool		is_invalid_pipe(t_tokenlist *tl);
	// DLIST
t_tokenlist	*tokenlist_create_node(t_data *data,
				void *content, t_tokentype type);
t_tokenlist	*tokenlist_push_front(t_data *data, t_tokenlist **tokenlist,
				void *content, t_tokentype type);
t_tokenlist	*tokenlist_push_back(t_data *data, t_tokenlist **tokenlist,
				void *content, t_tokentype type);
t_tokenlist	*tokenlist_insert_after(t_data *data, t_tokenlist *node,
				void *content, t_tokentype type);
void		tokenlist_remove_node(t_tokenlist **head, t_tokenlist *node);
t_filelist	*filelist_create_node(t_data *data, void *content, t_filetype type);
t_filelist	*filelist_push_front(t_data *data, t_filelist **filelist,
				void *content, t_filetype type);
t_filelist	*filelist_push_back(t_data *data, t_filelist **filelist,
				void *content, t_filetype type);
t_filelist	*filelist_getlast(t_filelist *filelist);
t_cmd_node	*cmdlist_create_node(t_data *data);
t_cmd_node	*cmdlist_push_front(t_data *data, t_cmd_node **cmdlist);
t_cmd_node	*cmdlist_push_back(t_data *data, t_cmd_node **cmdlist);
t_cmd_node	*cmdlist_getlast(t_cmd_node *cmdlist);

//	core/
	// core_loop.c
int			valid_minishell(int ac);
void		init_minishell(t_data *data, char **env);
void		handle_user_input(t_data *data);

//	builtins/
	// pwd.c
int			builtin_pwd(t_data *data);
int			builtin_echo(t_cmd_node *cmd_node);
int			builtin_env(t_data *data);
int			builtin_unset(t_data *data, t_cmd_node *cmd_node);
int			builtin_exit(t_data *data, t_cmd_node *cmd_node);
int			builtin_export(t_data *data, t_cmd_node *cmd_node);
int			builtin_cd(t_data *data, t_cmd_node *cmd_node);

// export_utils.c
char		*get_key(t_data *data, char *arg);
void		sort_env(t_data *data, char **env);
t_env_list	*get_env_by_key(t_data *data, char *key);
void		update_env_cpy(t_data *data);
void		add_new_var(t_data *data, char *key, char *value, bool is_null);
//	expand
void		find_expand(t_data *data);
// expand_utils
char		*ft_strjoin3(char *s1, char *s2, char *s3);
int			varlen(char *var);
char		*find_value(char *var, t_env_list *envlist);
char		*get_prefix(t_data *data, t_tokenlist *token, int *len);

//	data/
	//	init_data.c
int			init_data(t_data *data, char **env);

//	env_copy/
	//	env_list.c
t_env_list	*new_node_env_list(t_data *data, char *key, char *value);
void		push_back_env_list(t_env_list **env_list, t_env_list *new_node);
int			get_env_list_size(t_env_list *env_list);
	//	get_env_list.c
char		*get_env_key(char *env_line);
char		*get_env_value(char *env_line);
t_env_list	*get_env_list(t_data *data, char **env);
	//	get_env_copy.c
char		**get_env_copy(t_env_list *env_list);

//	error/
	//	free_and_exit.c
// void		free_and_exit(t_data *data, int exit_code);

void		free_and_exit_debug(t_data *data, int exit_code,
				const char *file, int line);

# define free_and_exit(data, exit_code) free_and_exit_debug(data, exit_code, __FILE__, __LINE__)

//	exec/
	//	builtins.c
int			exec_simple_cmd_builtins(t_cmd_node *cmd_node, t_data *data);
	//	cmd_path_case.c
int			cmd_is_directory(t_cmd_node *cmd_node, t_data *data);

	//	cmd_path.c
int			cmd_is_directory(t_cmd_node *cmd_node, t_data *data);
int			is_cmd_name_executable(t_cmd_node *cmd_node, t_data *data);
int			find_path_with_access(char **paths, char **pathname,
				t_data *data, t_cmd_node *cmd_node);
int			get_cmd_path_name(t_cmd_node *cmd_node, t_data *data);
	//	create_tmp_file.c
int			create_tmp_file(t_filelist *cur_file_in, t_data *data);
	//	dfl_env_list.c
t_env_list	*create_dfl_env_list(t_data *data);
	//	exec_pipe.c
int			exec_pipe(t_cmd_node *cmd_node, t_data *data);
	//	exec.c
int			exec(t_data *data);
int			exec_simple_cmd(t_cmd_node *cmd_node, t_data *data);
	//	extern.c
int			exec_simple_cmd_extern(t_cmd_node *cmd_node, t_data *data);
	//	env.c
char		*ft_getenv(t_data *data, char *key);
int			set_sh_lvl(t_data *data, char *str_sh_lvl);
	//	heredoc.c
int			create_heredoc(t_cmd_node *cmd_node, t_data *data);
	//	read_heredoc_fd.c
int			read_heredoc_fd(t_filelist *cur_file_in, t_data *data);
	//	redir_in_and_hd.c
int			exec_redir_in_and_hd(t_filelist	*file_in, t_data *data);
	//	redir_out_and_append.c
int			exec_redir_out_and_append(t_filelist *file_out, t_data *data);
	//	redirections.c
int			save_stdin_stdout(t_data *data);
int			reset_stdin_stdout(t_data *data);
int			exec_redirections(t_cmd_node *cmd_node, t_data *data);
	//	sh_level.c
int			sh_level(t_data *data);

//	memory/
	//	close_saved_fds.c
int			close_saved_fds(t_data *data);
	//	delete_tmp_file.c
void		delete_tmp_files(t_data *data);
	//	free_all.c
void		free_all(t_data *data, int exit_code);
	//	free_env_copy.c
void		free_env_copy(char **env_copy);
	//	free_env_list.c
void		free_env_list(t_env_list *env_list);
	//	free_tokens.c
void		free_tokenlist(t_tokenlist **tl);
	//	free_cmd_node.c
void		free_cmd_list(t_cmd_node **cmd_node);
	//	free_utils.c
void		free_matrix(char **split);

//	messsage/
	//	is_a_directory.c
void		msg_is_a_directory(t_data *data, int exit_code, char *name);
	//	error.c
void		msg_error(t_data *data, int exit_code, char *name);
	//	not_a_directory.c
void		msg_not_a_directory(t_data *data, int exit_code, char *name);
	//	redir_in_message.c
void		redir_in_message(char *filename, int err);
	//	msg_no_such_file_or_dir.c
void		msg_no_such_file_or_directory(t_data *data,
				int exit_code, char *cmd);
	//	msg_permission_denied.c
void		msg_permission_denied(t_data *data, int exit_code,
				char *filename);

//	signals/
	//	init_signals.c
void		init_signals(void);
void		sigint_handler(int sig);
void		heredoc_handler(int sig);

//	parsing_utils/
	//	check_quotes.c
bool		check_quotes(char *line);
	//	is_only_whitespace.c
bool		is_only_whitespace(char *line);
	//	secure_strdup.c
char		*secure_strdup(t_data *data, const char *s);

#endif
