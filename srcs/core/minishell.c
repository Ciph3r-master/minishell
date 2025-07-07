/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:25 by billcipher        #+#    #+#             */
/*   Updated: 2025/07/07 22:16:40 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"

int g_exit_status = 0;

// fonction a enlever quand on aurai le builtin env
#include "libft.h"
int	print_sh_lvl(t_data *data)
{
	t_env_list	*cur_env_list;

	cur_env_list = data->env_list;
	while (cur_env_list)
	{
		if (ft_strcmp(cur_env_list->key, "SHLVL") == 0)
		{
			printf("sh_lvl :%s\n", cur_env_list->value);
			return (1);
		}
		cur_env_list = cur_env_list->next;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_signals();
	init_data(&data, env);
	while (1)
	{
		if (save_stdin_stdout(&data.saved_stdin, &data.saved_stdout) == -1)
			free_and_exit(&data, 1);
		g_exit_status = 0;
		data.exec_heredoc = 1;
		data.line = readline("minishell> ");
		if (!data.line)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			free_and_exit(&data, data.exit_status);
		}
		free_cmd_list(&data.cmd_node);
		free_tokenlist(&data.tokenlist);
		add_history(data.line);
		if (g_exit_status == 1)
		{
			data.exit_status = g_exit_status;
			g_exit_status = 0;
		}
		init_tokens(&data);
		data.exit_status = 0;
		free(data.line);
		printf("\n ---------- exec -------\n\n");
		exec(&data);
		// printf("exit status:%d\n", data.exit_status);
		// print_sh_lvl(&data);
	}
	return (0);
}
