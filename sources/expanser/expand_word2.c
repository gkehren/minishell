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

void	set_incr_expand(int *i, char c)
{
	if (c == '$')
		(*i)++;
	else
		*i = 0;
}
