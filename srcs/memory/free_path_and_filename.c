/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path_and_filename.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-13 12:47:15 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-13 12:47:15 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

// itere dans un file_in et en
void	free_path_and_filename(t_filelist *cur_file_in)
{

	return (0);
}

// il faut qu'on fasse une fonction qui initialise tous
// les champs des structure a NULL
// ou 0
// ----------------------
// on va parcourir tous les noeud de filename_in
// et free tous les path_and_filename quand c'est un heredoc
void	free_path_and_filenames(t_data *data)
{
	t_cmd_node	*cur_cmd;

	if (!data || !data->cmd_node)
		return (-1);
	cur_cmd = data->cmd_node;
	while (cur_cmd)
	{
		free_path_and_filename(cur_cmd->file_in);
		cur_cmd = cur_cmd->next;
	}
}
