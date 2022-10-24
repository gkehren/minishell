#include "minishell.h"

static char	*file_exec(char *cmd)
{
	char	*tmp;
	int		i;
	int		j;

	i = 2;
	j = 0;
	tmp = ft_strdup(cmd);
	while (cmd[i])
	{
		cmd[j] = cmd[i];
		i++;
		j++;
	}
	cmd[i - 2] = '\0';
	if (access(tmp, X_OK) == 0)
		return (free(tmp), cmd);
	else
		return (print_error_str("minishell: ", tmp, ": "),
			set_status(126), perror(""), free(tmp), NULL);
}

static char	**split_env(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
	{
		if (!env[i])
			return (NULL);
		i++;
	}
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

int	check_abs_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '/' || cmd[i] == '.') && cmd[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*path_exec(char *cmd)
{
	int	fd;

	if (cmd[0] == '.' && cmd[1] == '/')
		return (file_exec(cmd));
	if (check_abs_path(cmd) == 1)
		fd = -1;
	else
		fd = open(cmd, O_RDONLY);
	if (fd == -1)
		return (print_error_str("minishell: ", cmd, ": Is a directory\n"),
			set_status(126), NULL);
	return (close(fd), cmd);
}

char	*path_command(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	if (cmd[0] == '\0')
		return (print_error("minishell: '': command not found\n"), NULL);
	paths = split_env(env);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_double_tab((void **)paths), path);
		free(path);
		i++;
	}
	return (free_double_tab((void **)paths),
		print_error_str("minishell: ", cmd, ": command not found\n"), NULL);
}
