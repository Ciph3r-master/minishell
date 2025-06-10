/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:45 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/04 18:17:52 by qutruche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>

enum e_type
{
	PIPE			= 1 << 0,
	REDIRECT_IN		= 1 << 1,
	HEREDOC			= 1 << 2,
	REDIRECT_OUT	= 1 << 3,
	APPEND			= 1 << 4,
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
	int			first_cmd;
	char		**filename_in;
	char		**filename_out;
	char		*delimiter;
	t_cmd		*cmd;
	t_cmd_node	*prev;
	t_cmd_node	*next;
}	t_cmd_node;

//	srcs/parsing/quotes.c
int		is_open_quotes(char *line, char quote);
char	*get_token(char *line, int *pos);
int		init_tokens(char *line);

#endif
