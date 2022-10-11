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

static void	parent_process(t_list *lcmd, char **env, int *fdd)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd[2];

	cmd = (t_cmd *)lcmd->content;
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		if (get_token_id(cmd->token_files) == IN)
			child_process_in();
		else if (get_token_id(cmd->token_files) == OUT)
			child_process_out(fd, fdd, env, lcmd);
		else
			child_process(fd, fdd, env, lcmd);
	}
	else
	{
		close(fd[1]);
		(*fdd) = fd[0];
		wait(NULL);
	}
}

int	exec(t_list *lcmd, t_list *venv)
{
	//t_cmd		*cmd;
	int			fdd;

	fdd = 0;
	while (lcmd)
	{
		//cmd = (t_cmd *)lcmd->content;
		//if (get_token_id(cmd->token_files) == IN)
		//	printf("INFILE\n");
		//else if (get_token_id(cmd->token_files) == OUT)
		//	parent_process_out(lcmd, send_env(&venv));
		//else
		parent_process(lcmd, send_env(&venv), &fdd);
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