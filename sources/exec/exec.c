/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/10 16:00:52 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_list *lcmd, t_list *venv)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd[2];
	int		fdd;

	fdd = 0;
	while (lcmd)
	{
		cmd = (t_cmd *)lcmd->content;
		pid = fork();
		if (pipe(fd) == -1)
			return (1);
		if (pid == -1)
			return (perror("fork"), 1);
		else if (pid == 0)
		{
			close(fd[0]);
			dup2(fdd, STDIN_FILENO);
			if (lcmd->next != NULL)
				dup2(fd[1], STDOUT_FILENO);
			if (execve(path_command(cmd->full_cmd[0], send_env(&venv)),
					cmd->full_cmd, send_env(&venv)) == -1)
				return (1);
		}
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
