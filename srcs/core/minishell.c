#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../includes/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (is_open_quotes(line, '"') || is_open_quotes(line, '\''))
			printf("Open quote\n");
		add_history(line);
	}
	rl_clear_history();
	return (0);
}