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

int	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	return (1);
}

int	print_error_char(char *error_b, char c, char *error_e)
{
	ft_putstr_fd(error_b, 2);
	write(2, &c, 1);
	ft_putstr_fd(error_e, 2);
	return (1);
}