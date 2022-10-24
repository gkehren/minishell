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
