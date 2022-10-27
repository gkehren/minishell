#include "minishell.h"

#define ERROR_MSG "minishell: pwd: -"
#define ERROR_MSG2 "minishell: pwd: --: invalid option\n"

static int	check_arg_pwd(int argc, char **args)
{
	int	i;

	if (argc > 1 && args[1][0] == '-')
	{
		i = 0;
		while (args[1][i] == '-' && args[1][i])
			i++;
		if (args[1][i] != '\0')
		{
			if (i == 1)
				return (set_status(2), print_error_char(ERROR_MSG,
						args[1][1], ": invalid option\n"));
			else
				return (set_status(2), print_error(ERROR_MSG2));
		}
	}
	return (0);
}

int	ft_pwd(int argc, char **args, t_list **venv, t_exec *exec)
{
	char		path[PATH_MAX];
	char		*tmp;

	(void)exec;
	if (check_arg_pwd(argc, args))
		return (1);
	if (getcwd(path, PATH_MAX) == NULL)
	{
		tmp = venv_find_content(venv, "PWD");
		if (tmp == NULL || ft_strlcpy(path, tmp, PATH_MAX) == 0)
		{
			perror("minishell: pwd: .\n");
			return (set_status(1), 1);
		}
	}
	printf("%s\n", path);
	return (0);
}
