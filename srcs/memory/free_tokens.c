/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:33:36 by bill              #+#    #+#             */
/*   Updated: 2025/07/19 03:14:32 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_tokenlist(t_tokenlist **tl)
{
	t_tokenlist	*current;
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
