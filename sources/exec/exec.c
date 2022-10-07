/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/07 14:26:03 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *path, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
			return (1);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	exec(t_list *lcmd, t_list *venv)
{
	t_cmd	*cmd;
	int		i;

	while (lcmd)
	{
		i = 0;
		cmd = (t_cmd *)lcmd->content;
		while (cmd->full_cmd[i])
		{
			// - manage redirection with token
			if (exec_cmd(path_command(cmd->full_cmd[i], send_env(&venv)),
					cmd->full_cmd, send_env(&venv)) == 1)
				return (1);
			//print_token_lex(cmd->token_files);
			//printf("\n");
			i++;
		}
		lcmd = lcmd->next;
	}
	return (0);
}
