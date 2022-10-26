#include "minishell.h"

int	expand_return_value(char **expand, char **str)
{
	char	*tmp;

	tmp = ft_itoa((long long)g_global.g_status);
	if (tmp == NULL)
		return (1);
	*expand = ft_strdup(tmp);
	if (*expand == NULL)
		return (free(tmp), 1);
	free(tmp);
	*str += 2;
	return (3);
}

/* Norminette functions */

void	init_begin(int *j, int i, char *begin, char *str)
{
	*j = -1;
	while (++(*j) != i)
		begin[*j] = str[*j];
	begin[*j] = '\0';
}

void	set_incr_expand(int *i, char c, t_expanse *expanse)
{
	(void)expanse;
	if (c == '$')
		(*i)++;
	else
		*i = 0;
	if (c == '\"' || c == '\'')
	{
		(*i)++;
	}
	expanse->char_to_rem = 0;
	expanse->mode = REPLACE;
}

int	check_weird_expand(char *str)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	if (str[1] == '\"' && (count % 2 != 0))
		return (1);
	return (0);
}
