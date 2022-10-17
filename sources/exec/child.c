#include "minishell.h"

void	redirect_child(t_list *lcmd, t_cmd *cmd, int *fd, int *fdd)
{
	if (cmd->files->infile != -2)
	{
		dup2(cmd->files->infile, STDIN_FILENO);
		close(cmd->files->infile);
	}
	else
		dup2((*fdd), STDIN_FILENO);
	if (cmd->files->outfile != -2)
	{
		dup2(cmd->files->outfile, STDOUT_FILENO);
		close(cmd->files->outfile);
	}
	else
	{
		if (lcmd->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
	}
	close(*fdd);
	close(fd[0]);
	close(fd[1]);
}

void	child_process(int *fd, int *fdd, t_list *venv, t_list *lcmd)
{
	t_cmd	*cmd;
	char	*path;
	char	**env;

	cmd = (t_cmd *)lcmd->content;
	env = send_env(&venv);
	if (!cmd->full_cmd)
		exit(0);
	path = path_command(cmd->full_cmd[0], env);
	if (!path)
		return (perror("Minishell"), free_double_tab((void *)env), free(path));
	redirect_child(lcmd, cmd, fd, fdd);
	if (execve(path, cmd->full_cmd, env) == -1)
		return (free(path), perror("Minishell"), free_double_tab((void *)env));
}

void	child_process_builtins(int *fd, int *fdd, t_list *venv, t_list *lcmd, t_builtins builtins)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)lcmd->content;
	redirect_child(lcmd, cmd, fd, fdd);
	(*builtins)(cmd->argc, cmd->full_cmd, &venv);
	ft_lstclear(&lcmd, &del_cmd);
	ft_lstclear(&venv, &del_venv);
	exit(0);
}
