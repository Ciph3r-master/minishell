#include "minishell.h"
#include <stdlib.h>

void	free_tokenlist(t_tokenlist **tl)
{
	t_tokenlist *current;
	t_tokenlist	*tmp;

	if (!tl || !*tl)
		return ;
	current = *tl;
	while (current)
	{
		tmp = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = tmp;
	}
	*tl = NULL;
}