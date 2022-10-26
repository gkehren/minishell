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
			return (1);
		tmp_list = tmp_list->next;
	}
	return (0);
}

char	*venv_find_content(t_list **venv, char *title)
{
	t_list	*tmp_list;
	t_venv	*tmp_venv;

	tmp_list = *venv;
	while (tmp_list)
	{
		tmp_venv = (t_venv *)tmp_list->content;
		if (!ft_strcmp(tmp_venv->title, title))
			return (tmp_venv->content);
		tmp_list = tmp_list->next;
	}
	return (NULL);
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
			free(title);
			free(tmp_venv->content);
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

	new = init_venv(title, content, set);
	if (new == NULL)
		return (1);
	tmp_list = ft_lstnew((void *)new);
	if (tmp_list == NULL)
		return (1);
	ft_lstadd_back(venv, tmp_list);
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
