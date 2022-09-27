#include "minishell.h"

char	*find_title_expand(char *str)
{
	int		i;
	int		j;
	char	*title;

	if (ft_isdigit(str[0]) || str[0] == '!' || str[0] == '@')
		i = 1;
	else
	{
		i = 0;
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	}
	title = (char *)malloc(sizeof(char) * (i + 1));
	if (title == NULL)
		return (NULL);
	if (i == 1)
		title[0] = str[0];
	else
	{
		j = 0;
		while (j < i)
		{
			title[j] = str[j];
			j++;
		}
		title[j] = '\0';
	}
	printf("title is %s\n", title);
	return (title);
}

int	expand_word(t_expanse expanse, t_list *venv, char *str, int i)
{
	int		j;
	char	*result;

	(void)venv;
	if (expanse.mode == PASS)
		return (0);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (1);
	j = 0;
	while (j != i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	// find_title_word;
	// find_env_word;
	// join_env_word;
	return (0);
}