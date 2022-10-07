#include "minishell.h"

int	pwd(int argc, char **argv, t_list **venv)
{
	char		path[PATH_MAX];
	char		*tmp;

	(void)argc;
	if (argv[1] != NULL)
		return (1);
	getcwd(path, PATH_MAX);
	if (path == NULL)
	{
		tmp = venv_find_content(venv, "PWD");
		if (tmp == NULL || ft_strlcpy(path, tmp, PATH_MAX) == 0)
		{
			perror("minishell: pwd: .");
			return (1);
		}
	}
	printf("%s\n", path);
	return (0);
}