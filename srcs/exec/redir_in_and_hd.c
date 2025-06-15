/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_and_hd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:27:53 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/15 15:39:40 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

// en premier je vais faire les redir_in et les redir_out
// c´est a dire
// que je vais faire c'est faire une fonction pour changer le stdin vers le fd
// de stdin vers le fd avec dup 2
// avec le dernier des file_in puisque c'est lui qui "gagne"
// puis une fonction avec les redir_out
// je vais aller chercher le dernier redir_out pour
// mettre le fd dans le stdout le remplacer par le fd
// avant ca je peut verifier si un redir_in existe
// ou si un redir_out existe

// sur chaque fichier je dois faire la redirect in
// c'est simplement la derniere qui restera le fd qui fera la
// redirection

// je dois passer sur tous les cur_file_in

// si c'est un FILE_IN
	// je dois verifier si le fichier existe avec open
	// si il n'existe pas je dois pas le creer
	// je le lis uniquement
	// je met son fd sur stdin_fileno
	// je close le fd si on a pu l'ouvrir
	// si on a pas de fd (toujour a -1)
	// on doit ecrire
	// minishell: <filename>: No such file or directory
	// et on n'execute pas la suite du programme

// si c'est un FILE_OUT


int	exec_redir_in(t_filelist *cur_file_in)
{
	(void)cur_file_in;
	return (1);
}

int	exec_redir_in_and_hd(t_filelist	*file_in)
{
	t_filelist	*cur_file_in;
	int			exec_out;

	if (!file_in)
		return (-1);
	cur_file_in = file_in;
	while (cur_file_in)
	{
		if (!cur_file_in->type)
			return (-1);
		if (FILE_IN == cur_file_in->type)
		{
			exec_out = exec_redir_in(cur_file_in);
			if (-1 == exec_out)
				return (-1);
			if (-2 == exec_out)
				return (-2);
		}
		// if (FILE_HD == cur_file_in->type)
		// 	exec_redir_hd(cur_file_in);
		cur_file_in = cur_file_in->next;
	}
	return (exec_out);
}
