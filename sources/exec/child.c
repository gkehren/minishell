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
	if (lcmd->next != NULL)
		close(*fdd);
	close(fd[0]);
	close(fd[1]);
}

void	child_process(int *fd, int *fdd, t_list **venv, t_list *lcmd)
{
	t_cmd	*cmd;
	char	*path;
	char	**env;

	cmd = (t_cmd *)lcmd->content;
	env = send_env(venv);
	if (!cmd->full_cmd)
		exit(0);
	path = path_command(cmd->full_cmd[0], env);
	if (!path)
		return (write(2, "Minishell: command not found\n", 30),
			free_double_tab((void *)env), free(path), close(fd[1]),
			close(fd[0]), free_exec(lcmd, *venv));
	redirect_child(lcmd, cmd, fd, fdd);
	if (execve(path, cmd->full_cmd, env) == -1)
		return (free(path), close(*fdd), perror("Minishell"), free_double_tab((void *)env));
}

void	child_process_builtins(int *fd, int *fdd, t_exec *exec, t_list *lcmd)
{
	t_cmd		*cmd;
	t_builtins	builtins;

	cmd = (t_cmd *)lcmd->content;
	builtins = (t_builtins)cmd->builtin;
	redirect_child(lcmd, cmd, fd, fdd);
	(*builtins)(cmd->argc, cmd->full_cmd, exec->venv);
	ft_lstclear(exec->cmd, &del_cmd);
	ft_lstclear(exec->venv, &del_venv);
	exit(0);
}