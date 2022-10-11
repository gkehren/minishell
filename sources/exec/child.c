#include "minishell.h"

void	child_process(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)lcmd->content;
	close(fd[0]);
	dup2((*fdd), STDIN_FILENO);
	if (lcmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		exit(1);
}

void	child_process_out(int *fd, int *fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;
	int		outfile;

	(void)fdd;
	cmd = (t_cmd *)lcmd->content;
	outfile = open(get_token_content(lcmd),
			O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile == -1)
		exit(1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	dup2(outfile, STDOUT_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		exit(1);
	close(outfile);
}

void	child_process_in(void)
{}

//static void	parent_process_out(t_list *lcmd, char **env)
//{
//	dup2(fd[0], STDIN_FILENO);
//	close(fd[1]);
//	dup2(outfile, STDOUT_FILENO);
//	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
//		exit(1);
//	close(outfile);
//}