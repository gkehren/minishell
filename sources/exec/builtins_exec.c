#include "minishell.h"

int	only_builtins(t_builtins p_builtins, t_cmd *cmd, t_list *venv, t_exec *exec)
{
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	if (cmd->files->infile != -2)
		dup2(cmd->files->infile, STDIN_FILENO);
	if (cmd->files->outfile != -2)
		dup2(cmd->files->outfile, STDOUT_FILENO);
	(*p_builtins)(cmd->argc, cmd->full_cmd, &venv, exec);
	if (cmd->files->infile != -2)
	{
		dup2(tmp_stdin, STDIN_FILENO);
		close(cmd->files->infile);
	}
	if (cmd->files->outfile != -2)
	{
		dup2(tmp_stdout, STDOUT_FILENO);
		close(cmd->files->outfile);
	}
	return (close(tmp_stdin), close(tmp_stdout), 0);
}
