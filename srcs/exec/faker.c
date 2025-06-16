#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"

t_data *init_sample_data_simple_cmd(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));

	if (!data || !cmd_node || !cmd)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));

	cmd->cmd = strdup("ls");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("ls");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	cmd_node->type = EXTERN;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = NULL;
	cmd_node->file_out = NULL;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = NULL;
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;

	return data;
}

t_data *init_sample_data_complex_cmd(void)
{
	t_data *data = malloc(sizeof(t_data));
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc = malloc(sizeof(t_filelist));
	t_filelist *file_out1 = malloc(sizeof(t_filelist));
	t_filelist *file_out2 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc || !file_out1 || !file_out2)
		return NULL;

	memset(data, 0, sizeof(t_data));
	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));
	memset(heredoc, 0, sizeof(t_filelist));
	memset(file_out1, 0, sizeof(t_filelist));
	memset(file_out2, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2");
	file2->type = FILE_IN;
	file2->next = heredoc;
	file2->prev = file1;

	heredoc->fd = 0;
	heredoc->limiter = strdup("EOF");
	heredoc->type = FILE_HD;
	heredoc->next = NULL;
	heredoc->prev = file2;

	file_out1->fd = 1;
	file_out1->filename = strdup("file_out_1");
	file_out1->type = FILE_OUT;
	file_out1->next = file_out2;
	file_out1->prev = NULL;

	file_out2->fd = 1;
	file_out2->filename = strdup("file_out_2");
	file_out2->type = FILE_OUT;
	file_out2->next = NULL;
	file_out2->prev = file_out1;

	cmd_node->type = EXTERN | REDIRECT_IN | HEREDOC | REDIRECT_OUT;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = file1;
	cmd_node->file_out = file_out1;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = strdup("< file_in_1 < file_in_2 << EOF cat > file_out_1 > file_out_2");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return data;
}
