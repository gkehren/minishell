#include "minishell.h"

static void	swap_token(t_list **prec, t_list **current,
	t_list **next, t_list **bg_lst)
{
	t_list	*tmp;

	if (*prec != NULL)
		(*prec)->next = *next;
	if (*current == *bg_lst)
		*bg_lst = *next;
	tmp = (*next)->next;
	(*next)->next = *current;
	(*current)->next = tmp;
}

static void	swap_token_files(t_list **token_files)
{
	t_list		*tmp_list;
	t_token_lex	*tmp_token;
	t_token_lex	*tmp_token_next;
	t_list		*prec;
	int			booli;

	booli = 0;
	prec = NULL;
	tmp_list = *token_files;
	while (tmp_list->next)
	{
		tmp_token = (t_token_lex *)tmp_list->content;
		tmp_token_next = (t_token_lex *)tmp_list->next->content;
		if (tmp_token->token == OUT || tmp_token->token == OUT_APPEND)
			booli = 1;
		if ((tmp_token_next->token == IN && booli == 1)
			|| (tmp_token_next->token == IN_HEREDOC && booli == 1))
			return (swap_token(&prec, &tmp_list, &tmp_list->next, token_files));
		prec = tmp_list;
		tmp_list = tmp_list->next;
	}
}

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
				fd = open(tmp_token->content, O_APPEND | O_WRONLY | O_CREAT,
						0644);
			else if (tmp_token->token == OUT)
				fd = open(tmp_token->content, O_TRUNC | O_WRONLY | O_CREAT,
						0644);
			else
				fd = open(tmp_token->content, O_RDONLY);
			if (fd == -1)
				return (set_status(1), print_error_str("minishell: ",
						tmp_token->content, ": "),
					print_error_char(strerror(errno), '\n', NULL), 1);
			close(fd);
		}
		token_list = token_list->next;
	}
	return (0);
}

static t_files	*set_files(t_list **token_list, t_list *venv, int index)
{
	t_files	*files;

	files = (t_files *)malloc(sizeof(t_files));
	if (files == NULL)
		return (NULL);
	files->is_heredoc = 0;
	files->infile = -2;
	files->outfile = -2;
	files->index_cmd = index;
	files->index_cmd_str = NULL;
	if (check_files(*token_list))
		return (free(files), NULL);
	while (is_sort_token_files(*token_list))
		swap_token_files(token_list);
	if (init_infile(*token_list, files, venv))
		return (free(files), NULL);
	if (init_outfile(*token_list, files))
		return (free(files), NULL);
	return (files);
}

int	init_files_cmd(t_list *cmd, t_list *venv)
{
	t_cmd	*tmp_cmd;
	int		index;

	index = 0;
	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		tmp_cmd->files = set_files(&tmp_cmd->token_files, venv, index);
		if (tmp_cmd->files == NULL)
			return (1);
		index++;
		cmd = cmd->next;
	}
	return (0);
}
