#include "minishell.h"

t_token_lex	*ft_lstnew_tl(char *content, t_token token)
{
	t_token_lex	*new;

	new = (t_token_lex *)malloc(sizeof(t_token_lex));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	ft_lstdelone(t_token_lex *lst)
{
	if (lst->content)
		ft_free((void **)&lst->content);
	ft_free((void **)&lst);
}

void	ft_lstclear(t_token_lex *bg_lst)
{
	t_token_lex	*current;

	if (!bg_lst)
		return ;
	current = bg_lst;
	while (bg_lst)
	{
		bg_lst = bg_lst->next;
		ft_lstdelone(current);
		current = bg_lst;
	}
}
