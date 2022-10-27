#include "minishell.h"

int	error_before(char **args)
{
	if (!(args[1]))
		return (0);
	if (args[1][0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(args[1][0], 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (set_status(2), 1);
	}
	return (0);
}

static int	parsing_str_export_unset(char *str)
{
	int	i;

	if (check_char_export(str[0], 0))
		return (1);
	i = 0;
	while (str[i])
	{
		if (check_char_export(str[i], 1))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(int argc, char **args, t_list **venv, t_exec *exec)
{
	int	i;

	(void)exec;
	(void)argc;
	set_status(0);
	if (error_before(args))
		return (1);
	i = 0;
	while (args[i])
	{
		if (parsing_str_export_unset(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			set_status(1);
		}
		else
			venv_remove(venv, args[i]);
		i++;
	}
	return (0);
}
