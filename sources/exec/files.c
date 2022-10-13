#include "minishell.h"

static int	check_files(t_list *token_list)
{
	t_token_lex	*tmp_token;
	int			fd;

	while (token_list)
	{
		tmp_token = (t_token_lex *)token_list->content;
		if (tmp_token->token != IN_HEREDOC)
		{
			if (tmp_token->token == OUT_APPEND)
				fd = open(tmp_token->content, O_RDONLY | O_CREAT, 0644);
			else
				fd = open(tmp_token->content, O_RDONLY);
			if (fd == -1)
			{
				print_error_str("minishell: ", tmp_token->content, ": ");
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				close (fd);
				return (1);
			}
			close(fd);
		}
		token_list = token_list->next;
	}
	return (0);
}

static t_files	*set_files(t_list *token_list, t_list *venv)
{
	t_files	*files;

	files = (t_files *)malloc(sizeof(t_files));
	if (files == NULL)
		return (NULL);
	if (check_files(token_list))
		return (free(files), NULL);
	if (init_infile(token_list, files, venv))
		return (free(files), NULL);
	if (init_outfile(token_list, files))
		return (free(files), NULL);
	return (files);
}

int	init_files_cmd(t_list *cmd, t_list *venv)
{
	t_cmd	*tmp_cmd;

	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		tmp_cmd->files = set_files(tmp_cmd->token_files, venv);
		if (tmp_cmd->files == NULL)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
