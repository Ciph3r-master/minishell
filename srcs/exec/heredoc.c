/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/13 02:30:40 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// au final c'est quoi un heredoc
// c'est, on creer un fichier temporaire
// il faudra le supprimer apres son execution dans
// les execution des redir_in avec unlink()
// on utilise le nom du fichier temporaire
// pour creer le fichier


// fd = open("mon_fichier.txt", O_RDWR | O_CREAT, 0644);
// if (fd == -1) {

// on va ensuite ouvrir readline dans une boucle infinie
// on va lire la ligne,
// si la ligne est egale au delimiteur
// :
//	on vas ecrire la derniere line et ajouter '\0'
//	on va fermer le fichier
//	on sort de la boucle
// si on as ctrl + D donc EOF, (\n ?)
// on doit ecrire la phrase du ctrl d et quitter le readline
// la ligne que j'ai ecrit dans ma line doit etre ecrite dans
// le fd de mon fichier ouvert avec write(fd, , )
//
int	run_heredoc(t_filelist *cur_file_in)
{
	int	fd;

	fd = create_tmp_file(cur_file_in);
	if (-1 == fd)
		return (-1);
	return (1);
}

int	run_heredoc_in_file_in(t_filelist *cur_file_in)
{
	while (cur_file_in)
	{
		if (cur_file_in->type == FILE_HD)
		{
			if (run_heredoc(cur_file_in) == -1)
				return (-1);
		}
		cur_file_in = cur_file_in->next;
	}
	return (0);
}

// cette fonction va parcourir tous les node
// pour verifier si il on des heredoc, si oui on les cree
// puis on les execute, avec la gestion des signaux
// donc ouvrir un readline qui attend le oef present dans la structure
// on les execute un a un jusqu'a que la file_list soit vide
int	exec_heredoc(t_cmd_node *cmd_node)
{
	t_cmd_node	*cur_cmd;

	if (!cmd_node)
		return (-1);
	cur_cmd = cmd_node;
	while (cur_cmd)
	{
		if (-1 == run_heredoc_in_file_in(cur_cmd->file_in))
			return (-1);
		cur_cmd = cur_cmd->next;
	}
	return (1);
}
