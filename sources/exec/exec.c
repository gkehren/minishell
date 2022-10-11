/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/11 13:55:46 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(int *fd, int *fdd, char **env, t_list *lcmd)
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

static void	parent_process(t_list *lcmd, char **env, int *fdd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		child_process(fd, fdd, env, lcmd);
	else
	{
		close(fd[1]);
		(*fdd) = fd[0];
		wait(NULL);
	}
}

static void	parent_process_out(t_list *lcmd, char **env)
{
	t_cmd	*cmd;
	int		outfile;
	int		fd[2];

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

int	exec(t_list *lcmd, t_list *venv)
{
	t_cmd		*cmd;
	int			fdd;

	fdd = 0;
	while (lcmd)
	{
		cmd = (t_cmd *)lcmd->content;
		if (get_token_id(cmd->token_files) == IN)
			printf("IN LETSGO\n");
		else if (get_token_id(cmd->token_files) == OUT)
			parent_process_out(lcmd, send_env(&venv));
		else
			parent_process(lcmd, send_env(&venv), &fdd);
		lcmd = lcmd->next;
	}
	return (0);
}
