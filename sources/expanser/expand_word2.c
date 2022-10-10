#include "minishell.h"

int	expand_return_value(char **expand, char **str)
{
	char	*tmp;

	tmp = ft_itoa((long long)42);
	if (tmp == NULL)
		return (1);
	*expand = ft_strdup(tmp);
	if (*expand == NULL)
		return (free(tmp), 1);
	free(tmp);
	*str += 2;
	return (3);
}
