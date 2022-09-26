#include "minishell.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
	//ft_free((void **)&lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		ft_lstdelone(current, del);
		current = *lst;
	}
	*lst = NULL;
}
