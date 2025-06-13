/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:05:13 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/13 19:49:52 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include "libft.h"

// au final c'est quoi un heredoc
// c'est, on creer un fichier temporaire
// il faudra le close et supprimer apres son execution dans
// les execution des redir_in avec unlink()
// ou a la sortie du programme
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

int	readline_heredoc(char *here_line, char *limiter, int fd)
{
	here_line = readline("> ");
	if (!here_line)
	{
		write(1, "ctrl+d in heredoc, EOF\n", 23);
		free(here_line);
		return (0);
	}
	if (ft_strcmp(limiter, here_line) == 0)
	{
		free(here_line);
		return (0);
	}
	write(fd, here_line, ft_strlen(here_line));
	write(fd, "\n", 1);
	free(here_line);
	return (1);
}

int	read_heredoc_fd(t_filelist *cur_file_in)
{
	char	*here_line;
	char	*limiter;
	int		fd;
	int		read;

	limiter = cur_file_in->limiter;
	fd = cur_file_in->fd;
	here_line = NULL;
	read = 1;
	while (read)
		read = readline_heredoc(here_line, limiter, fd);
	if (close(fd) == -1)
		return (-1);
	cur_file_in->fd = -1;
	return (0);
}

int	run_heredoc(t_filelist *cur_file_in)
{
	cur_file_in->fd = create_tmp_file(cur_file_in);
	if (cur_file_in->fd == -1)
		return (-1);
	if (read_heredoc_fd(cur_file_in) == -1)
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
