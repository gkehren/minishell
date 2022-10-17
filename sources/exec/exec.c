/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/17 18:19:52 by genouf           ###   ########.fr       */
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

int	parent_process(t_list *lcmd, char **env, int *fdd)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd[2];

	if (init_parent_process(lcmd, &pid, &cmd, &fd))
		return (free_double_tab((void *)env), 1);
	if (pid == 0)
	{
		if (get_token_id(cmd->token_files) == IN)
			child_process_in(fd, fdd, env, lcmd);
		else if (get_token_id(cmd->token_files) == OUT
			|| get_token_id(cmd->token_files) == OUT_APPEND)
			child_process_out(fd, fdd, env, lcmd);
		else
			child_process(fd, fdd, env, lcmd);
	}
	else
	{
		free_double_tab((void *)env);
		close(fd[1]);
		(*fdd) = fd[0];
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
		else if (parent_process(lcmd, send_env(&venv), &fdd) == 1)
			return (exec_error(lcmd, venv), 1);
		lcmd = lcmd->next;
	}
	return (0);
}
