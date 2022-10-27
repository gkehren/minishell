/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:24:19 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:24:21 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_builtins(t_cmd *cmd, int tmp_stdin, int tmp_stdout)
{
	if (cmd->files->outfile != -2)
		close(cmd->files->outfile);
	if (cmd->files->infile != -2)
		close(cmd->files->infile);
	close(tmp_stdin);
	close(tmp_stdout);
}

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
	if (ft_strcmp(cmd->full_cmd[0], "exit") == 0)
		close_builtins(cmd, tmp_stdin, tmp_stdout);
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
