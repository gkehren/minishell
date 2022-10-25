#include "minishell.h"

static int	check_char_export(char c, int mode)
{
	if (mode == 0)
	{
		if (c != '_' && !(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z'))
			return (1);
		else
			return (0);
	}
	else
	{
		if (c != '_' && !(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')
			&& !(c >= '0' && c <= '9'))
			return (1);
		else
			return (0);
	}
}

static int	parsing_str_export(char *str)
{
	int	i;

	if (check_char_export(str[0], 0))
		return (1);
	i = 0;
	while (str[i] && (str[i] != '=' && (str[i] != '+' || str[i + 1] != '=')))
	{
		if (check_char_export(str[i], 1))
			return (1);
		i++;
	}
	return (0);
}

int	parsing_export(char **args)
{
	int	i;

	i = 1;
	if (args[1][0]== '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(args[1][0], 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (set_status(2), 1);
	}
	while (args[i])
	{
		if (parsing_str_export(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (set_status(1), 1);
		}
		i++;
	}
	return (0);
}
