#include "minishell.h"

int	export_concat(t_list **venv, char *title_env, char **new_content)
{
	char	*result;

	result = ft_strjoin(venv_find_content(venv, title_env), *new_content);
	if (result == NULL)
		return (1);
	free(*new_content);
	*new_content = result;
	return (0);
}

char	**malloc_not_init(char *env_part)
{
	char	**result;
	int		i;

	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL)
		return (NULL);
	result[0] = (char *)malloc(sizeof(char) * (ft_strlen(env_part) + 1));
	if (result[0] == NULL)
		return (NULL);
	i = 0;
	while (env_part[i])
	{
		result[0][i] = env_part[i];
		i++;
	}
	result[0][i] = '\0';
	result[1] = NULL;
	return (result);
}

int	malloc_failed_env(t_list **venv)
{
	ft_lstclear(venv, &del_venv);
	printf("ENV creation failed !\n");
	return (1);
}

static int	begin_env_i(t_list **venv)
{
	char	**args;

	args = ft_split("export OLPWD", ' ');
	if (args == NULL)
		return (1);
	ft_export(0, args, venv, NULL);
	free_double_tab((void **)args);
	args = ft_split("export SHLVL=1", ' ');
	if (args == NULL)
		return (1);
	ft_export(0, args, venv, NULL);
	free_double_tab((void **)args);
	args = ft_split("export _=/usr/bin/env", ' ');
	if (args == NULL)
		return (1);
	ft_export(0, args, venv, NULL);
	free_double_tab((void **)args);
	return (0);
}

int	init_env_i(t_list **venv, char **args)
{
	char	*tmp;
	char	*tmp2;
	char	path[PATH_MAX];

	begin_env_i(venv);
	if (getcwd(path, PATH_MAX) == NULL)
		return (1);
	tmp = ft_strjoin("PWD=", path);
	if (tmp == NULL)
		return (1);
	tmp2 = tmp;
	tmp = ft_strjoin("export ", tmp);
	if (tmp == NULL)
		return (free(tmp2), 1);
	free(tmp2);
	args = ft_split(tmp, ' ');
	if (args == NULL)
		return (free(tmp), 1);
	free(tmp);
	ft_export(0, args, venv, NULL);
	free_double_tab((void **)args);
	return (0);
}
