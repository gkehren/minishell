#include "minishell.h"

int	unset(t_list **venv, char **args, int status_ret)
{
	int	i;

	(void)status_ret;
	i = 0;
	while (args[i])
	{
		venv_remove(venv, args[i]);
		i++;
	}
	return (0);
}
