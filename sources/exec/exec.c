/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/11 19:22:45 by genouf           ###   ########.fr       */
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

int	parent_process(t_list *lcmd, char **env, int *fdd)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd[2];

	cmd = (t_cmd *)lcmd->content;
	pid = fork();
	if (pipe(fd) == -1 || pid == -1)
		return (free_double_tab((void *)env), 1);
	else if (pid == 0)
	{
		if (get_token_id(cmd->token_files) == IN)
			child_process_in(fd, fdd, env, lcmd);
		else if (get_token_id(cmd->token_files) == OUT)
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
	int	fdd;

	fdd = 0;
	while (lcmd)
	{
		if (parent_process(lcmd, send_env(&venv), &fdd) == 1)
			return (exec_error(lcmd, venv), 1);
		lcmd = lcmd->next;
	}
	return (0);
}

		//if (current_b != NULL && nb_cmd == 1)
		//	only_builtins(current_b, tmp, exec);
		//else
		//{
		//	if (current_b != NULL)
		//		body_fork_builtins(current_b, tmp, exec, nb_cmd);
		//	else
		//		body_fork(exec, tmp, nb_cmd);
		//}
