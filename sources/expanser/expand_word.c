#include "minishell.h"

static int	join_env_word(char *begin, char *expand, char **str, char *tmp_str)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(begin, expand);
	if (result == NULL)
		return (free(begin), free(expand), free(tmp_str), 1);
	free(begin);
	tmp = ft_strdup(*str);
	if (tmp == NULL)
		return (free(tmp_str), free(result), 1);
	*str = ft_strjoin(result, tmp);
	if (*str == NULL)
		return (free(tmp_str), free(result), 1);
	free(result);
	free(tmp);
	free(tmp_str);
	return (0);
}

static char	*find_env_word(t_list *venv, char *title)
{
	t_venv	*tmp_venv;

	if (title[0] == '\0')
	{
		free(title);
		return (NULL);
	}
	title += 1;
	while (venv)
	{
		tmp_venv = (t_venv *)venv->content;
		if (!ft_strcmp(tmp_venv->title, title))
		{
			title -= 1;
			free(title);
			return (tmp_venv->content);
		}
		venv = venv->next;
	}
	title -= 1;
	free(title);
	return (NULL);
}

static int	find_size_title(char *str, int *i)
{
	*i = 1;
	if (str[1] == '$' || str[1] == '\0' || check_weird_expand(str))
		return (2);
	else if (str[1] == '\'' || str[1] == '\"')
		*i = 0;
	else if (str[1] == '?' || ft_isdigit(str[1])
		|| !(ft_isalnum(str[1]) || str[1] == '_'))
	{
		*i = 2;
		if (ft_isdigit(str[1]))
			return (0);
		else if (str[1] == '?')
			return (3);
		else
			return (2);
	}
	else
	{
		*i = 1;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
	}
	return (0);
}

static int	find_title_expand(char **str, char **expand, int it)
{
	int	i;
	int	j;
	int	returned;

	*str += it;
	returned = find_size_title(*str, &i);
	if (returned == 3)
		return (expand_return_value(expand, str));
	*expand = (char *)malloc(sizeof(char) * (i + 1));
	if (*expand == NULL)
		return (1);
	j = 0;
	while (j < i)
	{
		(*expand)[j] = (*str)[j];
		j++;
	}
	(*expand)[j] = '\0';
	if (i == 0)
		i = 1;
	*str += i;
	return (returned);
}

int	expand_word(t_expanse expanse, t_list *venv, char **str, int *i)
{
	int		j;
	char	*begin;
	char	*expand;
	char	*tmp2;

	tmp2 = *str;
	if (expanse.mode == PASS)
		return (0);
	begin = (char *)malloc(sizeof(char) * (*i + 1));
	if (begin == NULL)
		return (free(tmp2), 1);
	init_begin(&j, *i, begin, *str);
	j = find_title_expand(str, &expand, *i);
	if (j == 1)
		return (free(tmp2), free(begin), 1);
	else if (j == 0)
		expand = find_env_word(venv, expand);
	if (join_env_word(begin, expand, str, tmp2))
		return (1);
	if (j != 0)
		free(expand);
	return (0);
}
