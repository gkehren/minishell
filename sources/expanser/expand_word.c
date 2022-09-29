#include "minishell.h"

// static char *join_env_word(char *begin, char *expand)
// {
// 	char	*result;

// 	result = ft_strjoin(begin, expand);

// }

static char	*find_env_word(t_list *venv, char *title)
{
	t_venv	*tmp_venv;

	while (venv)
	{
		tmp_venv = (t_venv *)venv->content;
		if (!ft_strcmp(tmp_venv->title, title))
		{
			free(title);
			return (tmp_venv->content);
		}
		venv = venv->next;
	}
	free(title);
	return (NULL);
}

static void	find_size_title(char *str, int *i)
{
	if (ft_isdigit(str[0]) || str[0] == '!' || str[0] == '@')
		*i = 1;
	else
	{
		*i = 0;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
	}
}

static char	*find_title_expand(char **str)
{
	int		i;
	int		j;
	char	*title;

	find_size_title(*str, &i);
	title = (char *)malloc(sizeof(char) * (i + 1));
	if (title == NULL)
		return (NULL);
	if (i == 1)
	{
		title[0] = (*str)[0];
		title[1] = '\0';
	}
	else
	{
		j = 0;
		while (j < i)
		{
			title[j] = (*str)[j];
			j++;
		}
		title[j] = '\0';
	}
	*str += i;
	return (title);
}

int	expand_word(t_expanse expanse, t_list *venv, char *str, int i)
{
	int		j;
	char	*begin;
	char	*tmp;

	if (expanse.mode == PASS)
		return (0);
	begin = (char *)malloc(sizeof(char) * (i + 1));
	if (begin == NULL)
		return (1);
	j = 0;
	while (j != i)
	{
		begin[j] = str[j];
		j++;
	}
	begin[j] = '\0';
	//printf("last word is %c\n", begin[j - 1]);
	str += (i + 1);
	tmp = find_title_expand(&str);
	printf("debut str = %c\n", *str);
	tmp = find_env_word(venv, tmp);
	printf("content of expand is %s\n", tmp);
	//join_env_word(begin, tmp);
	return (0);
}