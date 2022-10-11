#include "minishell.h"

int	ft_unset(int argc, char **args, t_list **venv)
{
	int	i;

	(void)argc;
	i = 0;
	while (args[i])
	{
		venv_remove(venv, args[i]);
		i++;
	}
	return (0);
}
