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
	PIPE			= 1 << 0,
	REDIRECT_IN		= 1 << 1,
	REDIRECT_OUT	= 1 << 2,
	APPEND			= 1 << 3,
	HEREDOC			= 1 << 4,
	EXTERN			= 1 << 5,
	BUILTIN			= 1 << 6,
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

// srcs/builtins/pwd.c
int	builtin_pwd(void);

#endif
