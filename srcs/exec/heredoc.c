/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 17:05:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-12 17:05:13 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// au final c'est quoi un heredoc
// c'est, on creer un fichier temporaire
// il faudra le supprimer apres son execution dans
// les execution des redir_in
// on utilise le nom du fichier temporaire
// pour creer le fichier

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
int	run_heredoc(t_cmd_node *cmd_node)
{

}

// cette fonction va parcourir tous les node
// pour verifier si il on des heredoc, si oui on les cree
// puis on les execute, avec la gestion des signaux
// donc ouvrir un readline qui attend le oef present dans la structure
// on les execute un a un jusqu'a que la file_list soit vide
int	exec_heredoc(t_cmd_node *cmd_node)
{
	t_cmd_node	*current;

	current = cmd_node;
	while (current)
	{
		if (current->file_in->type == FILE_HD)
		{
			if (run_heredoc(current) == -1)
				return (-1);
			return (0);
		}
		current->next;
	}
	return (1);
}

