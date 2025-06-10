/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-10 11:58:30 by thmaitre          #+#    #+#             */
/*   Updated: 2025-06-10 11:58:30 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ########## INIT CMD_NODE ##############################

// fonction servant a imiter le pasring en creant des fausse
// donne en liste chainee qui vont etre envoyé a ma fonction exec
// comme si le parsing avais envoyé ces données
t_cmd_node	*cmd_node_list(t_cmd_node *cmd_node)
{
	return (cmd_node);
}

// ########## EXEC HEREDOC ##############################

int	exec_heredoc(t_cmd_node *cmd_node)
{

}

// ########## EXEC ##############################

// ma fonction principale de mon execution
// va executer les heredoc
// executer une commmande simple dans un enfant ou non si un builtin
// -> executer les redir_in a l'interieur de la commande
// -> executer les redir_out a l'interieur de la commande
// executer les pipe si il y en a, et donc creer des fork pour chaque pipe, avec un old et new_pipe
// -> a l'interieur de chaque cmd executer les redir_in a l'interieur
// -> a l'interieur de chaque cmd executer les redir_out a l'interieur
int	exec(t_cmd_node *cmd_node)
{
	int	node_type;

	node_type = INT_MIN;
	// cette fonction va parcourir tous les node
	// pour verifier si il on des heredoc, si oui on les cree
	// puis on les execute, avec la gestion des signaux
	// donc ouvrir un readline qui attend le oef present dans la structure
	// on les execute un a un jusqu'a que la file_list soit vide
	exec_heredoc(cmd_node);
	if (!cmd_node->next)
	{
		if (BUILTIN & node_type)
			// va permettre d'executer une commande en builtin
			// donc on va juste aller chercher la commande
			// dans un dossier builtin et l'executer
			// a l'interieur on va aussi executer
			// les redir_in puis les redir_out
			// ??? apres l'execution on dois rendre les sortie classique ???
			exec_simple_cmd_builtin(cmd_node);
		if (EXTERN & node_type)
			// va permettre d'executer une commande en extern
			// on va creer un fork simple pour simplement executer
			// avant d'executer on va faire les redir_in, puis les redir_out
			exec_simple_cmd_extern(cmd_node);
	}
	else if (cmd_node->next)
	{
		// on va dans une boucle, executer chaque commande suivi d'un pipe
		// on va faire les redirection des pipe avant celle
		// des redir_in et de redir_out, pour chaque commande
		// puis on fait les redir_in et out, ainsi on a les redir qui prennent
		// la priorité sur les pipes
		execute_pipe(cmd_node);
	}
}

// fonction servant a imiter le pasring en creant des fausse
// donne en liste chainee qui vont etre envoyé a ma fonction exec
// comme si le parsing avais envoyé ces données
// puis va appeler mon exec
// cette fonction simule aussi le comportement des signaux
// pour pouvoir implementer les cas sprciaux dans les heredoc
// : ce qui signifie
// 		quand on lance les commande on doit rendre le comportement normal des signaux
//		pendant l'exec, (alors les fonction externe vont le faire nativement mais les fonction
//		builtin vont devoir recuperer les signaux classique ???)
// 			dans les heredoc les gerer comme dans bash,
//				ctrl \ : fait rien
//				ctrl C : ecrit ^C quitte EOF, free, et rend le prompt noeuf, ne fait
//					pas la suite des commandes
//				ctrl D : - bash: warning: here-document at line 133 delimited by end-of-file (wanted `EOF') --------> printf(%s) le delimiter
//		 - on ferme le fichier temp
//		 - on execute la suite
int	main(int argc, char **argv, char **env)
{
	t_cmd_node	*cmd_node;

	cmd_node = init_cmd_node_list(cmd_node);
	exec(cmd_node);
}
