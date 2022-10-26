#include "minishell.h"

int	ft_unset(int argc, char **args, t_list **venv, t_exec *exec)
{
	int	i;

	(void)exec;
	(void)argc;
	if (parsing_export(args))
		return (1);
	i = 0;
	while (args[i])
	{
		venv_remove(venv, args[i]);
		i++;
	}
	return (0);
}
