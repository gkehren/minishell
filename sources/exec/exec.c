/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/06 03:13:54 by gkehren          ###   ########.fr       */
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
	char	**args;

	args = malloc(2 * sizeof(char *));
	args[0] = malloc(3 * sizeof(char));
	args[0] = "ls";
	args[1] = malloc(3 * sizeof(char));
	args[1] = "-l";
	(void)venv;
	while (lcmd)
	{
		i = 0;
		cmd = (t_cmd *)lcmd->content;
		while (cmd->full_cmd[i])
		{
			// - manage redirection with token
			// - need parse arg of each command
			// - need env as char **
			exec_cmd("/bin/ls", args, NULL);
			//print_token_lex(cmd->token_files);
			//printf("\n");
			i++;
		}
		lcmd = lcmd->next;
	}
	return (0);
}
