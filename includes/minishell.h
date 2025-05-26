#ifndef MINISHELL_H
#define MINISHELL_H

enum e_type
{
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	CMD,
	ARGS,
};

int	is_open_quotes(char *line, char quote);

#endif