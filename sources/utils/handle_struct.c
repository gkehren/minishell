#include "minishell.h"

t_token_lex	*init_token_lex(char *content, t_token token)
{
	t_token_lex	*token_lex;

	token_lex = (t_token_lex *)malloc(sizeof(t_token_lex));
	if (token_lex == NULL)
		return (NULL);
	token_lex->content = content;
	token_lex->token = token;
	token_lex->heredoc_ex = 0;
	return (token_lex);
}

void	del_token_lex(void *lst)
{
	t_token_lex	*tmp;

	tmp = (t_token_lex *)lst;
	free(tmp->content);
	free(tmp);
}

t_venv	*init_venv(char *title, char *content, t_set set)
{
	t_venv	*venv;

	venv = (t_venv *)malloc(sizeof(t_venv));
	if (venv == NULL)
		return (NULL);
	venv->title = title;
	venv->content = content;
	venv->set = set;
	return (venv);
}

void	del_venv(void *lst)
{
	t_venv	*tmp;

	tmp = (t_venv *)lst;
	free(tmp->title);
	if (tmp->content)
		free(tmp->content);
	free(tmp);
}

void	del_cmd(void *lst)
{
	t_cmd	*tmp;

	tmp = (t_cmd *)lst;
	free(tmp->full_path);
	free_double_tab((void **)tmp->full_cmd);
	ft_lstclear(&tmp->token_files, &del_token_lex);
	free(lst);
}
