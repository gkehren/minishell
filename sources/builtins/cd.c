#include "minishell.h"

static int	set_up_env_var(t_list **venv)
{
	char	path[PATH_MAX];
	char	*tmp;

	if (getcwd(path, PATH_MAX) == NULL)
		return (set_status(1), perror("minishell: cd"), 1);
	tmp = ft_strdup(path);
	if (tmp == NULL)
		return (1);
	if (malloc_cd("PWD", venv, tmp) == 1)
		return (1);
	return (0);
}

static int	swap_pwd_env(t_list **venv)
{
	char	*old_pwd;

	old_pwd = ft_strdup(venv_find_content(venv, "PWD"));
	if (old_pwd == NULL)
		return (1);
	if (malloc_cd("OLDPWD", venv, old_pwd) == 1)
		return (1);
	if (set_up_env_var(venv))
		return (1);
	return (0);
}

static char	*return_env_path(int argc, char **args, t_list **venv)
{
	char	*path;

	if (argc == 1)
		path = venv_find_content(venv, "HOME");
	else
	{
		if (args[1][0] == '-')
			path = venv_find_content(venv, "OLDPWD");
		else if (args[1][0] == '~')
			path = venv_find_content(venv, "HOME");
		else
			path = args[1];
	}
	return (path);
}

static int	check_errors(int argc, char **args, t_list **venv)
{
	if (argc > 2)
		return (set_status(1),
			print_error("minishell: cd: too many arguments\n"));
	if ((argc == 1 && !venv_exist(venv, "HOME")) || (venv_exist(venv, "HOME")
			&& venv_find_content(venv, "HOME") == NULL))
		return (set_status(1), print_error("minishell: cd: HOME not set \n"));
	if (argc == 2 && args[1][0] == '-')
	{
		if (args[1][1] != '-')
			return (set_status(2), print_error_str("minishell: cd: ",
					args[1], " :invalid option\n"));
		else if (args[1][2] != '\0')
			return (set_status(2),
				print_error("minishell: cd: --: invalid option\n"));
	}
	if (argc == 2 && args[1][0] == '-' && !venv_exist(venv, "OLDPWD"))
		return (set_status(1), print_error("minishell: cd: OLDPWD not set \n"));
	return (0);
}

int	ft_cd(int argc, char **args, t_list **venv, t_exec *exec)
{
	char	*path;
	int		ret;

	(void)exec;
	if (check_errors(argc, args, venv))
		return (1);
	path = return_env_path(argc, args, venv);
	if (set_up_env_var(venv))
		return (1);
	if (path[0] == '\0')
		ret = 0;
	else
		ret = chdir(path);
	if (ret == 0)
	{
		if (swap_pwd_env(venv))
			return (1);
	}
	else
	{
		set_status(1);
		print_cd_error(path, strerror(errno));
	}
	return (ret);
}
