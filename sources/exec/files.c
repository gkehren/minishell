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
			fd = open(tmp_token->content, O_RDONLY);
			if (fd == -1)
			{
				print_error_str("minishell: ", tmp_token->content, ": ");
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}

static int	init_infile(t_list *token_list, t_files *files, t_list *venv)
{
	t_token_lex	*tmp_token;
	t_list		*last_lst;
	t_heredoc	heredoc_var;

	last_lst = ft_lstlast(token_list);
	while (token_list)
	{
		tmp_token = (t_token_lex *)token_list->content;
		if (token_list == last_lst)
			break ;
		if (tmp_token->token == IN_HEREDOC)
		{
			heredoc_var = init_heredoc_var(tmp_token->content, tmp_token->heredoc_ex, files, 0);
			heredoc(heredoc_var, venv);
		}
		token_list = token_list->next;
	}
	if (tmp_token->token == IN)
		files->infile = open(tmp_token->content, O_RDONLY);
	else if (tmp_token->token == IN_HEREDOC)
	{
		heredoc_var = init_heredoc_var(tmp_token->content, tmp_token->heredoc_ex, files, 0);
		if (heredoc(heredoc_var, venv))
			return (1);
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
	return (NULL);
}

void	init_files_cmd(t_list *cmd, t_list *venv)
{
	t_cmd	*tmp_cmd;

	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		tmp_cmd->files = set_files(tmp_cmd->token_files, venv);
		cmd = cmd->next;
	}
}