#include "../../includes/minishell.h"

int	is_open_quotes(char *line, char quote)
{
	int	i;
	int	is_open;

	i = 0;
	while (line[i])
	{
		if (line[i] == quote && !is_open)
			is_open = 1;
		else if (line[i] == quote)
			is_open = 0;
		i++;
	}
	return (is_open);
}