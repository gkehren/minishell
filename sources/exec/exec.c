/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/18 01:55:42 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(t_list *lcmd, t_list *venv)
{
	perror("Minishell");
	ft_lstclear(&lcmd, &del_cmd);
	ft_lstclear(&venv, &del_venv);
	exit(1);
}

static void	init_exec(t_exec *exec, t_list **lcmd, t_list **venv)
{
	exec->cmd = lcmd;
	exec->venv = venv;
}

int	exec(t_list **lcmd, t_list **venv)
{
	t_cmd	*cmd;
	t_exec	exec;
	int		fdd;
	int		size_cmd;
	t_list	*tmp_list;

	tmp_list = *lcmd;
	fdd = 0;
	init_exec(&exec, lcmd, venv);
	size_cmd = ft_lstsize(*lcmd);
	while (tmp_list)
	{
		cmd = (t_cmd *)(tmp_list)->content;
		if (cmd->builtin != NULL && size_cmd == 1)
			only_builtins(cmd->builtin, cmd, *venv);
		else if (parent_process(&exec, tmp_list, &fdd) == 1)
			return (exec_error(tmp_list, *venv), 1);
		if (cmd->files->is_heredoc == 1)
		{
			if (delete_tmp())
				return (1);
		}
		tmp_list = (tmp_list)->next;
	}
	return (0);
}
