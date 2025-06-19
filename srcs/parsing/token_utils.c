#include "minishell.h"
#include "libft.h"

bool is_redirection(t_tokentype type)
{
	return (type == TRD_IN || type == TRD_OUT || type == TAPPEND || type == THD);
}

int	is_operator(char *line)
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

int	is_builtin(char *word)
{
	const char	*builtin[8];
	int			i;

	i = 0;
	builtin[0] = "ECHO"; //ECHO
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
