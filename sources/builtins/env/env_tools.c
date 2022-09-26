#include "minishell.h"

int	venv_exist(t_list **venv, char *title)
{
	t_list	*tmp_list;
	t_venv	*tmp_venv;

	tmp_list = *venv;
	while (tmp_list)
	{
		tmp_venv = (t_venv *)tmp_list->content;
		if (!ft_strcmp(tmp_venv->title, title))
			return (0);
		tmp_list = tmp_list->next;
	}
	return (1);
}

void	venv_replace(t_list **venv, char *title, char *content)
{
	t_list	*tmp_list;
	t_venv	*tmp_venv;

	tmp_list = *venv;
	while (tmp_list)
	{
		tmp_venv = (t_venv *)tmp_list->content;
		if (!ft_strcmp(tmp_venv->title, title))
		{
			free(tmp_venv->content);
			free(title);
			tmp_venv->content = content;
			tmp_venv->set = INIT;
			return ;
		}
		tmp_list = tmp_list->next;
	}
}

int	venv_create(t_list **venv, char *title, char *content, t_set set)
{
	t_list	*tmp_list;
	t_venv	*new;

	tmp_list = ft_lstlast(*venv);
	new = init_venv(title, content, set);
	if (new == NULL)
		 return (1);
	tmp_list->next = ft_lstnew((void *)new);
	return (0);
}

void	venv_remove(t_list **venv, char *title)
{
	t_list	*current;
	t_list	*prec;
	t_venv	*tmp_venv;

	prec = NULL;
	current = *venv;
	while (current)
	{
		tmp_venv = (t_venv *)current->content;
		if (!ft_strcmp(tmp_venv->title, title))
		{
			if (prec == NULL)
				*venv = current->next;
			else
				prec->next = current->next;
			ft_lstdelone(current, &del_venv);
			return ;
		}
		prec = current;
		current = current->next;
	}
}
