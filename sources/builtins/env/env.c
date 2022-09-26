#include "minishell.h"

char	**send_env(t_list **venv)
{
	char	**env;
	char	*tmp_str;
	t_list	*tmp_list;
	t_venv	*tmp_venv;
	int		i;

	env = (char **)malloc(sizeof(char *) * (ft_lstsize(*venv) + 1));
	if (env == NULL)
		return (NULL);
	tmp_list = *venv;
	i = 0;
	while (tmp_list)
	{
		tmp_venv = (t_venv *)tmp_list->content;
		tmp_str = ft_strjoin(tmp_venv->title, "=");
		env[i] = ft_strjoin(tmp_str, tmp_venv->content);
		free(tmp_str);
		i++;
		tmp_list = tmp_list->next;
	}
	env[i] = 0;
	return (env);
}

void	env(t_list **venv, char **args, int status_ret)
{
	t_list	*tmp_list;
	t_venv	*tmp_venv;

	(void)args;
	(void)status_ret;
	tmp_list = *venv;
	while (tmp_list)
	{
		tmp_venv = (t_venv *)tmp_list->content;
		if (tmp_venv->set == INIT)
			printf("%s=%s\n", tmp_venv->title, tmp_venv->content);
		tmp_list = tmp_list->next;
	}
}
