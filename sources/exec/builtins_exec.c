#include "minishell.h"

 int	only_builtins(t_builtins p_builtins, t_cmd *cmd, t_list *venv)
 {
 	int	tmp_stdin;
 	int	tmp_stdout;
 	//int	check1;
 	//int	check2;

 	tmp_stdin = dup(STDIN_FILENO);
 	tmp_stdout = dup(STDOUT_FILENO);
 	if (tmp_stdin == -1 || tmp_stdout == -1)
 		return (print_error("Dup failed !\n"));
 	//check1 = dup2(cmd->infile.fd, STDIN_FILENO);
 	//check2 = dup2(cmd->outfile.fd, STDOUT_FILENO);
 	//if (check1 == -1 || check2 == -1)
 	//	return (print_error("Dup2 failed !\n"));
 	(*p_builtins)(cmd->argc, cmd->full_cmd, &venv);
 	dup2(tmp_stdin, STDIN_FILENO);
 	dup2(tmp_stdout, STDOUT_FILENO);
 	//if (check1 == -1 || check2 == -1)
 	//	return (print_error("Dup2 failed !\n"));
 	return (0);
 }
