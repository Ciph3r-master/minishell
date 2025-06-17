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

	cmd->cmd = strdup("ertef");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("ertef");
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

t_data *init_cmd_redir_in(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = NULL;
	file1->prev = NULL;

	cmd_node->type = EXTERN | REDIRECT_IN;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = file1;
	cmd_node->file_out = NULL;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = strdup("< file_in_1 cat");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return data;
}

t_data *init_cmd_multi_redir_in(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc = malloc(sizeof(t_filelist));
	t_filelist *file_out1 = malloc(sizeof(t_filelist));
	t_filelist *file_out2 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc || !file_out1 || !file_out2)
		return (NULL);

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = NULL;
	file2->prev = file1;

	cmd_node->type = EXTERN | REDIRECT_IN;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = file1;
	cmd_node->file_out = NULL;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = strdup("< file_in_1 < file_in_2 cat");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return (data);
}

t_data *init_cmd_multi_redir_in_heredoc(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));
	memset(heredoc, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = heredoc;
	file2->prev = file1;

	heredoc->fd = 0;
	heredoc->limiter = strdup("EOF");
	heredoc->type = FILE_HD;
	heredoc->next = NULL;
	heredoc->prev = file2;

	cmd_node->type = EXTERN | REDIRECT_IN | HEREDOC;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = file1;
	cmd_node->file_out = NULL;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = strdup("< file_in_1 < file_in_2 << EOF cat");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return (data);
}

t_data *init_cmd_multi_redir_in_multi_heredoc(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc1 = malloc(sizeof(t_filelist));
	t_filelist *heredoc2 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc1 || !heredoc2)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));
	memset(heredoc1, 0, sizeof(t_filelist));
	memset(heredoc2, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = heredoc1;
	file2->prev = file1;

	heredoc1->fd = 0;
	heredoc1->limiter = strdup("EOF1");
	heredoc1->type = FILE_HD;
	heredoc1->next = heredoc2;
	heredoc1->prev = file2;

	heredoc2->fd = 0;
	heredoc2->limiter = strdup("EOF2");
	heredoc2->type = FILE_HD;
	heredoc2->next = NULL;
	heredoc2->prev = heredoc1;

	cmd_node->type = EXTERN | REDIRECT_IN | HEREDOC;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = file1;
	cmd_node->file_out = NULL;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = strdup("< file_in_1 < file_in_2 << EOF1 << EOF2 cat");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return (data);
}

t_data *init_cmd_multi_redir_in_multi_heredoc_redir_out(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc1 = malloc(sizeof(t_filelist));
	t_filelist *heredoc2 = malloc(sizeof(t_filelist));
	t_filelist *file_out1 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc1 || !heredoc2 || !file_out1)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));
	memset(heredoc1, 0, sizeof(t_filelist));
	memset(heredoc2, 0, sizeof(t_filelist));
	memset(file_out1, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = heredoc1;
	file2->prev = file1;

	heredoc1->fd = 0;
	heredoc1->limiter = strdup("EOF1");
	heredoc1->type = FILE_HD;
	heredoc1->next = heredoc2;
	heredoc1->prev = file2;

	heredoc2->fd = 0;
	heredoc2->limiter = strdup("EOF2");
	heredoc2->type = FILE_HD;
	heredoc2->next = NULL;
	heredoc2->prev = file2;

	file_out1->fd = 1;
	file_out1->filename = strdup("file_out_1.txt");
	file_out1->type = FILE_OUT;
	file_out1->next = NULL;
	file_out1->prev = NULL;

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

	data->line = strdup("< file_in_1 < file_in_2 << EOF1 << EOF2 cat > file_out_1");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return data;
}

t_data *init_cmd_multi_redir_in_multi_heredoc_multi_redir_out(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc1 = malloc(sizeof(t_filelist));
	t_filelist *heredoc2 = malloc(sizeof(t_filelist));
	t_filelist *file_out1 = malloc(sizeof(t_filelist));
	t_filelist *file_out2 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc1 || !heredoc2 || !file_out1 || !file_out2)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));
	memset(heredoc1, 0, sizeof(t_filelist));
	memset(heredoc2, 0, sizeof(t_filelist));
	memset(file_out1, 0, sizeof(t_filelist));
	memset(file_out2, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = heredoc1;
	file2->prev = file1;

	heredoc1->fd = 0;
	heredoc1->limiter = strdup("EOF1");
	heredoc1->type = FILE_HD;
	heredoc1->next = heredoc2;
	heredoc1->prev = file2;

	heredoc2->fd = 0;
	heredoc2->limiter = strdup("EOF2");
	heredoc2->type = FILE_HD;
	heredoc2->next = NULL;
	heredoc2->prev = file2;

	file_out1->fd = 1;
	file_out1->filename = strdup("file_out_1.txt");
	file_out1->type = FILE_OUT;
	file_out1->next = file_out2;
	file_out1->prev = NULL;

	file_out2->fd = 1;
	file_out2->filename = strdup("file_out_2.txt");
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

	data->line = strdup("< file_in_1.txt < file_in_2.txt << EOF1 << EOF2 cat > file_out_1.txt > file_out_2.txt");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return data;
}

t_data *init_cmd_multi_redir_in_multi_heredoc_multi_redir_out_append(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc1 = malloc(sizeof(t_filelist));
	t_filelist *heredoc2 = malloc(sizeof(t_filelist));
	t_filelist *file_out1 = malloc(sizeof(t_filelist));
	t_filelist *file_out2 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc1 || !heredoc2 || !file_out1 || !file_out2)
		return NULL;

	memset(cmd_node, 0, sizeof(t_cmd_node));
	memset(cmd, 0, sizeof(t_cmd));
	memset(file1, 0, sizeof(t_filelist));
	memset(file2, 0, sizeof(t_filelist));
	memset(heredoc1, 0, sizeof(t_filelist));
	memset(heredoc2, 0, sizeof(t_filelist));
	memset(file_out1, 0, sizeof(t_filelist));
	memset(file_out2, 0, sizeof(t_filelist));

	cmd->cmd = strdup("cat");
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = strdup("cat");
	cmd->args[1] = NULL;
	cmd->pathname = NULL;

	file1->fd = 0;
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = heredoc1;
	file2->prev = file1;

	heredoc1->fd = 0;
	heredoc1->limiter = strdup("EOF1");
	heredoc1->type = FILE_HD;
	heredoc1->next = heredoc2;
	heredoc1->prev = file2;

	heredoc2->fd = 0;
	heredoc2->limiter = strdup("EOF2");
	heredoc2->type = FILE_HD;
	heredoc2->next = NULL;
	heredoc2->prev = file2;

	file_out1->fd = 1;
	file_out1->filename = strdup("file_out_1.txt");
	file_out1->type = FILE_OUT;
	file_out1->next = file_out2;
	file_out1->prev = NULL;

	file_out2->fd = 1;
	file_out2->filename = strdup("file_out_2.txt");
	file_out2->type = FILE_APPEND;
	file_out2->next = NULL;
	file_out2->prev = file_out1;

	cmd_node->type = EXTERN | REDIRECT_IN | HEREDOC | REDIRECT_OUT | APPEND;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 1;
	cmd_node->error_code = 0;
	cmd_node->file_in = file1;
	cmd_node->file_out = file_out1;
	cmd_node->delimiter = NULL;
	cmd_node->cmd = cmd;
	cmd_node->prev = NULL;
	cmd_node->next = NULL;

	data->line = strdup("< file_in_1.txt < file_in_2.txt << EOF1 << EOF2 cat > file_out_1.txt >> file_out_2.txt");
	data->cmd_node = cmd_node;
	data->pwd = NULL;
	data->old_pwd = NULL;
	data->env_list = NULL;
	data->env_copy = NULL;

	return data;
}

t_data *init_sample_data_complex_cmd(t_data *data)
{
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_filelist *file1 = malloc(sizeof(t_filelist));
	t_filelist *file2 = malloc(sizeof(t_filelist));
	t_filelist *heredoc = malloc(sizeof(t_filelist));
	t_filelist *file_out1 = malloc(sizeof(t_filelist));
	t_filelist *file_out2 = malloc(sizeof(t_filelist));

	if (!data || !cmd_node || !cmd || !file1 || !file2 || !heredoc || !file_out1 || !file_out2)
		return NULL;

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
	file1->filename = strdup("file_in_1.txt");
	file1->type = FILE_IN;
	file1->next = file2;
	file1->prev = NULL;

	file2->fd = 0;
	file2->filename = strdup("file_in_2.txt");
	file2->type = FILE_IN;
	file2->next = heredoc;
	file2->prev = file1;

	heredoc->fd = 0;
	heredoc->limiter = strdup("EOF");
	heredoc->type = FILE_HD;
	heredoc->next = NULL;
	heredoc->prev = file2;

	file_out1->fd = 1;
	file_out1->filename = strdup("file_out_1.txt");
	file_out1->type = FILE_OUT;
	file_out1->next = file_out2;
	file_out1->prev = NULL;

	file_out2->fd = 1;
	file_out2->filename = strdup("file_out_2.txt");
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
