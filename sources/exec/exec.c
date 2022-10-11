/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/11 01:57:16 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(int *fd, int fdd, char **env, t_list *lcmd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)lcmd->content;
	close(fd[0]);
	dup2(fdd, STDIN_FILENO);
	if (lcmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (execve(path_command(cmd->full_cmd[0], env), cmd->full_cmd, env) == -1)
		exit(1);
}

int	exec(t_list *lcmd, t_list *venv)
{
	pid_t	pid;
	int		fd[2];
	int		fdd;

	fdd = 0;
	while (lcmd)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		else if (pid == 0)
			child_process(fd, fdd, send_env(&venv), lcmd);
		else
		{
			close(fd[1]);
			fdd = fd[0];
			wait(NULL);
			lcmd = lcmd->next;
		}
	}
	return (0);
}
