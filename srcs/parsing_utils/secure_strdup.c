/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:31:00 by vscode            #+#    #+#             */
/*   Updated: 2025/07/19 03:20:36 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*secure_strdup(t_data *data, const char *s)
{
	char	*dup;
	int		i;

	dup = NULL;
	i = 0;
	while (s[i])
		i++;
	dup = malloc(sizeof (*s) * i + 1);
	if (!dup)
		free_and_exit(data, 1);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
