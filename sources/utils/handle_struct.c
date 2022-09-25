#include "minishell.h"

t_token_lex	*init_token_lex(char *content, t_token token)
{
	t_token_lex	*token_lex;

	token_lex = (t_token_lex *)malloc(sizeof(t_token_lex));
	if (token_lex == NULL)
		return (NULL);
	token_lex->content = content;
	token_lex->token = token;
	return (token_lex);
}

void	del_token_lex(void *lst)
{
	t_token_lex	*tmp;

	tmp = (t_token_lex *)lst;
	if (tmp->content && tmp->token == WORD)
		ft_free((void **)&tmp->content);
	ft_free((void **)&tmp);
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
	ft_free((void **)&tmp->title);
	if (tmp->content)
		ft_free((void **)&tmp->content);
}