#include "minishell.h"

static t_venv	**init_tab_sort(t_list **venv, int size_lst)
{
	t_venv	**tab_sort;
	t_list	*tmp_list;
	t_venv	*tmp_venv;
	int		i;

	i = 0;
	tmp_list = *venv;
	tab_sort = (t_venv **)malloc(sizeof(t_venv *) * size_lst);
	if (tab_sort == NULL)
	{
		printf("Malloc error !\n");
		return (NULL);
	}
	while (tmp_list)
	{
		tmp_venv = (t_venv *)tmp_list->content;
		tab_sort[i] = tmp_venv;
		i++;
		tmp_list = tmp_list->next;
	}
	return (tab_sort);
}

static t_venv	**sort_export(t_list **venv)
{
	t_venv	**tab_sort;
	t_venv	*tmp;
	int		size_lst;
	int		i;
	int		j;

	size_lst = ft_lstsize(*venv);
	tab_sort = init_tab_sort(venv, size_lst);
	if (tab_sort == NULL)
		return (NULL);
	i = -1;
	while (++i < size_lst - 1)
	{
		j = i;
		while (++j < size_lst)
		{
			if (ft_strcmp(tab_sort[i]->title, tab_sort[j]->title) > 0)
			{
				tmp = tab_sort[i];
				tab_sort[i] = tab_sort[j];
				tab_sort[j] = tmp;
			}
		}
	}
	return (tab_sort);
}

static void	export_print_all(t_list **venv)
{
	t_venv	**tab_sort;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(*venv);
	tab_sort = sort_export(venv);
	if (tab_sort == NULL)
		return ;
	while (i < size)
	{
		if (tab_sort[i]->set == INIT)
			printf("declare -x %s=\"%s\"\n",
				tab_sort[i]->title, tab_sort[i]->content);
		else
			printf("declare -x %s\n", tab_sort[i]->title);
		i++;
	}
	free(tab_sort);
}

static int	export_action(t_list **venv, char **cuting, char **args, int i)
{
	if (venv_exist(venv, cuting[0]) == 1)
	{
		if (find_char('=', args[i]))
			venv_replace(venv, cuting[0], cuting[1]);
		else
			return (free(cuting[0]), free(cuting[1]), 0);
	}
	else
	{
		if (find_char('=', args[i]))
		{
			if (venv_create(venv, cuting[0], NULL, NOT_INIT))
				return (1);
		}
		else
		{
			if (venv_create(venv, cuting[0], cuting[1], INIT))
				return (1);
		}
	}
	return (0);
}

int	ft_export(int argc, char **args, t_list **venv)
{
	int		i;
	char	**cuting;

	(void)argc;
	if (ft_strcmp(args[0], "export") == 0 && args[1] == NULL)
		export_print_all(venv);
	else
	{
		if (parsing_export(args))
			return (1);
		i = 1;
		while (args[i])
		{
			cuting = cut_env(args[i]);
			if (export_action(venv, cuting, args, i))
				return (free(cuting), 1);
			free(cuting);
			i++;
		}
	}
	return (0);
}
