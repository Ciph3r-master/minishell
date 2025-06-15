/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025/06/15 23:27:22 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	exec_builtins(t_cmd_node *cmd_node)
{
	char	*cmd;

	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd->cmd)
		return (-1);
	cmd = cmd_node->cmd->cmd;
	if (ft_strcmp("pwd", cmd))
		builtin_pwd();
	return (1);
}

// va permettre d'executer une commande en builtin
// donc on va juste aller chercher la commande
// dans un dossier builtin et l'executer
// a l'interieur on va aussi executer
// les redir_in puis les redir_out
// apres l'execution on dois rendre les sortie classique

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
int	exec_simple_cmd_builtins(t_cmd_node *cmd_node)
{
	int	node_type;
	int	exec_out;

	exec_out = 0;
	node_type = INT_MIN;
	if (!cmd_node || !cmd_node->type)
		return (-1);
	if (REDIRECT_IN & node_type || HEREDOC & node_type)
	{
		exec_out = exec_redir_in_and_hd(cmd_node->file_in);
		if (-1 == exec_out)
			return (-1);
		if (-2 == exec_out)
			return (-2);
	}
	if (REDIRECT_OUT & node_type || APPEND & node_type)
	{
		exec_out = exec_redir_out_and_append(cmd_node->file_in);
		if (-1 == exec_out)
			return (-1);
	}
	exec_builtins(cmd_node);
	// reset_in_out();
	return (exec_out);
}
