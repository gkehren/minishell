#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	good_token(int c)
{
	const char	token[] = {'$', '\"', '\'', '_', '-', '/', '.', '~', '?', '+', '\0'};
	int			i;

	i = 0;
	while (token[i])
	{
		if (c == token[i])
			return (1);
		i++;
	}
	return (0);
}
