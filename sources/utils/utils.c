#include "minishell.h"

int	find_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	save_quote(int booli, char c)
{
	if (c != '\'' && c != '\"')
		return (1);
	if (c == '\'' && booli == 1)
		return (1);
	if (c == '\"' && booli == 2)
		return (1);
	return (0);
}

void	set_status(int status)
{
	g_global.g_status = status;
}

int	malloc_cd(char *str, t_list **venv, char *tmp)
{
	str = ft_strdup(str);
	if (venv_exist(venv, str))
		venv_replace(venv, str, tmp);
	else
	{
		if (venv_create(venv, str, tmp, INIT))
			return (1);
	}
	return (0);
}
