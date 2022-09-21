#include "minishell.h"

t_token_lex	*init_token_lex(char *content, t_token token)
{
	t_token_lex	*new;

	new = (t_token_lex *)malloc(sizeof(t_token_lex));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token = token;
	return (new);
}

void	del_token_lex(void *lst)
{
	t_token_lex	*tmp;

	tmp = (t_token_lex *)lst;
	if (tmp->content && tmp->token == WORD)
		ft_free((void **)&tmp->content);
	ft_free((void **)&tmp);
}
