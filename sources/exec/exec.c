/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/06 14:35:39 by gkehren          ###   ########.fr       */
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
			exec_cmd("/bin/ls", cmd->full_cmd, send_env(&venv));
			//print_token_lex(cmd->token_files);
			//printf("\n");
			i++;
		}
		lcmd = lcmd->next;
	}
	return (0);
}
