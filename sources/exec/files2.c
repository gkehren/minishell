#include "minishell.h"

static t_list	*ft_lstlast_in(t_list *token_list)
{
	t_token_lex	*tmp_token;

	if (!token_list)
		return (NULL);
	tmp_token = (t_token_lex *)token_list->content;
	if ((tmp_token->token != IN && tmp_token->token != IN_HEREDOC))
		return (NULL);
	while (token_list->next)
	{
		tmp_token = (t_token_lex *)token_list->next->content;
		if (tmp_token->token == OUT || tmp_token->token == OUT_APPEND)
			return (token_list);
		token_list = token_list->next;
	}
	return (token_list);
}

static int	pro_init_outfile(t_token_lex *tmp_token, t_files *files)
{
	if (tmp_token->token == OUT)
		files->outfile = open(tmp_token->content, O_CREAT | O_TRUNC
				| O_WRONLY, 0644);
	else if (tmp_token->token == OUT_APPEND)
		files->outfile = open(tmp_token->content,
				O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (files->outfile == -1)
		return (1);
	return (0);
}

int	init_outfile(t_list *token_list, t_files *files)
{
	t_token_lex	*tmp_token;
	t_list		*last_lst;

	if (!token_list)
		return (0);
	last_lst = ft_lstlast_in(token_list);
	if (last_lst != NULL)
		token_list = last_lst->next;
	if (token_list == NULL)
		return (0);
	while (token_list->next)
	{
		tmp_token = (t_token_lex *)token_list->content;
		if (tmp_token->token == OUT || tmp_token->token == OUT_APPEND)
		{
			if (open(tmp_token->content, O_CREAT | O_WRONLY, 0644) == -1)
				return (1);
		}
		token_list = token_list->next;
	}
	if (pro_init_outfile((t_token_lex *)token_list->content, files))
		return (1);
	return (0);
}

static int	pro_init_infile(t_list *token_list, t_files *files,
	t_list *venv, t_heredoc hevar)
{
	t_token_lex	*tmp_token;

	if (token_list != NULL)
	{
		tmp_token = (t_token_lex *)token_list->content;
		if (tmp_token->token == IN)
			files->infile = open(tmp_token->content, O_RDONLY);
		else if (tmp_token->token == IN_HEREDOC)
		{
			hevar = init_heredoc_var(tmp_token->content,
					tmp_token->heredoc_ex, files, 1);
			if (heredoc(hevar, venv, NULL, dup(STDIN_FILENO)))
				return (1);
		}
	}
	else
		files->infile = -2;
	return (0);
}

int	init_infile(t_list *token_list, t_files *files, t_list *venv)
{
	t_token_lex	*tmp_token;
	t_list		*last_lst;
	t_heredoc	heredoc_var;

	last_lst = ft_lstlast_in(token_list);
	if (last_lst == NULL)
		return (0);
	while (token_list && token_list != last_lst)
	{
		tmp_token = (t_token_lex *)token_list->content;
		if (tmp_token->token == IN_HEREDOC)
		{
			heredoc_var = init_heredoc_var(tmp_token->content,
					tmp_token->heredoc_ex, files, 0);
			if (heredoc(heredoc_var, venv, NULL, dup(STDIN_FILENO)))
				return (1);
		}
		token_list = token_list->next;
	}
	if (pro_init_infile(token_list, files, venv, heredoc_var))
		return (1);
	return (0);
}
