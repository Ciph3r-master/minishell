/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_and_hd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-14 15:27:53 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-14 15:27:53 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	exec_redir_in_and_hd(t_filelist	*cur_file_in)
{

}
