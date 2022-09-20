#include "minishell.h"

int	ft_lstsize(void *lst)
{
	int		count;
	t_venv	*tmp;
	
	tmp = (t_venv *)lst;
	if (!tmp)
		return (0);
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	*ft_lstlast(void *lst)
{
	t_venv	*tmp;

	tmp = (t_venv *)lst;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back(void **bg_lst, void *new)
{
	t_venv	**bg_tmp;
	t_venv	*tmp;

	bg_tmp = (t_venv **)bg_lst;
	tmp = (t_venv *)new;
	if (!(*bg_tmp))
		*bg_tmp = tmp;
	else
	{
		tmp = ft_lstlast(*bg_tmp);
		tmp->next = tmp;
	}
}
