/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:45 by thmaitre          #+#    #+#             */
/*   Updated: 2025/05/28 01:00:51 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

enum e_type
{
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	EXTERN,
	BUILTIN,
};

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
}	t_cmd;

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	int			type;
	int			fd_in;
	int			fd_out;
	char		*filename_in;
	char		*filename_out;
	int			error_code;
	t_cmd		cmd;
	t_ast_node	*parent;
	t_ast_node	*right;
	t_ast_node	*left;
}	t_ast_node;

//	srcs/parsing/quotes.c
int	is_open_quotes(char *line, char quote);

// srcs/builtins/pwd.c
int	builtin_pwd(void);

#endif
