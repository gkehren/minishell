#include "minishell.h"

void	child_process(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;
	char	*path;

	cmd = (t_cmd *)lcmd->content;
	path = path_command(cmd->full_cmd[0], env);
	if (!path)
		return (perror("Minishell"), free_double_tab((void *)env), free(path));
	close(fd[0]);
	dup2((*fdd), STDIN_FILENO);
	if (lcmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (execve(path, cmd->full_cmd, env) == -1)
		return (perror("Minishell"), free_double_tab((void *)env), free(path));
}

void	child_process_out(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;
	char	*path;

	(void)fdd;
	cmd = (t_cmd *)lcmd->content;
	path = path_command(cmd->full_cmd[0], env);
	if (!path)
		return (perror("Minishell"), free_double_tab((void *)env), free(path));
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	dup2(cmd->files->outfile, STDOUT_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		return (free_double_tab((void *)env), free(path));
	close(cmd->files->outfile);
}

void	child_process_in(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;
	char	*path;

	(void)fdd;
	cmd = (t_cmd *)lcmd->content;
	path = path_command(cmd->full_cmd[0], env);
	if (!path)
		return (perror("Minishell"), free_double_tab((void *)env), free(path));
	close(fd[0]);
	dup2(cmd->files->infile, STDIN_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		return (free_double_tab((void *)env), free(path));
	close(cmd->files->infile);
}
