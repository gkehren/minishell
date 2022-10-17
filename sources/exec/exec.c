/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/18 00:22:16 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_error(t_list *lcmd, t_list *venv)
{
	perror("Minishell");
	ft_lstclear(&lcmd, &del_cmd);
	ft_lstclear(&venv, &del_venv);
	exit(1);
}

int	init_parent_process(t_list *lcmd, pid_t *pid, t_cmd **cmd, int (*fd)[])
{
	*cmd = (t_cmd *)lcmd->content;
	if (pipe(*fd) == -1)
		return (1);
	*pid = fork();
	if (*pid == -1)
		return (1);
	return (0);
}

int	parent_process(t_list *lcmd, t_list *venv, int *fdd)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd[2];

	if (init_parent_process(lcmd, &pid, &cmd, &fd))
		return (1);
	if (pid == 0)
	{
		if (cmd->builtin)
			child_process_builtins(fd, fdd, venv, lcmd, cmd->builtin);
		else
			child_process(fd, fdd, venv, lcmd);
	}
	else
	{
		close(fd[1]);
		(*fdd) = fd[0];
		if (lcmd->next == NULL)
			close(*fdd);
		if (cmd->files->infile != -2)
			close(cmd->files->infile);
		if (cmd->files->outfile != -2)
			close(cmd->files->outfile);
		wait(NULL);
	}
	return (0);
}

int	exec(t_list *lcmd, t_list *venv)
{
	t_cmd	*cmd;
	int		fdd;
	int		size_cmd;

	fdd = 0;
	size_cmd = ft_lstsize(lcmd);
	while (lcmd)
	{
		cmd = (t_cmd *)lcmd->content;
		if (cmd->builtin != NULL && size_cmd == 1)
			only_builtins(cmd->builtin, cmd, venv);
		else if (parent_process(lcmd, venv, &fdd) == 1)
			return (exec_error(lcmd, venv), 1);
		if (cmd->files->is_heredoc == 1)
		{
			if (delete_tmp())
				return (1);
		}
		lcmd = lcmd->next;
	}
	return (0);
}
