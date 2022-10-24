/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/24 09:50:52 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_list *lcmd, t_list *venv)
{
	ft_lstclear(&lcmd, &del_cmd);
	ft_lstclear(&venv, &del_venv);
	exit(1);
}

static void	init_struct_exec(t_exec *exec, t_list **lcmd, t_list **venv)
{
	exec->cmd = lcmd;
	exec->venv = venv;
}

static void	init_exec(int *size_cmd, t_list **tmp_list, t_list *lcmd)
{
	*size_cmd = ft_lstsize(lcmd);
	*tmp_list = lcmd;
}

int	exec(t_list **lcmd, t_list **venv, int fdd)
{
	t_cmd	*cmd;
	t_exec	exec;
	int		size_cmd;
	t_list	*tmp_list;

	init_exec(&size_cmd, &tmp_list, *lcmd);
	init_struct_exec(&exec, lcmd, venv);
	while (tmp_list)
	{
		cmd = (t_cmd *)(tmp_list)->content;
		if (cmd->builtin != NULL && size_cmd == 1)
			only_builtins(cmd->builtin, cmd, *venv, &exec);
		else if (parent_process(&exec, tmp_list, &fdd) == 1)
			return (free_exec(tmp_list, *venv), 1);
		if (cmd->files->is_heredoc == 1)
		{
			unlink(cmd->files->index_cmd_str);
			free(cmd->files->index_cmd_str);
		}
		tmp_list = (tmp_list)->next;
	}
	while (size_cmd--)
		wait(NULL);
	begin_signal();
	return (0);
}
