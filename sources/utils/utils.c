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

int	init_outfile_bis(t_token_lex *token)
{
	int	fd;

	if (token->token == OUT)
	{
		fd = open(token->content, O_CREAT | O_TRUNC | O_WRONLY,
				0644);
		if (fd == -1)
			return (1);
	}
	else if (token->token == OUT_APPEND)
	{
		fd = open(token->content, O_APPEND | O_WRONLY | O_CREAT,
				0644);
		if (fd == -1)
			return (1);
	}
	return (close(fd), 0);
}
