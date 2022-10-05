/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/05 19:35:12 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_list *lcmd, t_list *venv)
{
	t_cmd	*cmd;
	int		i;

	(void)venv;
	while (lcmd)
	{
		i = 0;
		cmd = (t_cmd *)lcmd->content;
		while (cmd->full_cmd[i + 1])
		{
			printf("EXEC: %s\n", cmd->full_cmd[i]);
			printf("PATH: %s\n", cmd->full_path);
			print_token_lex(cmd->token_files);
			printf("\n");
			i++;
		}
		lcmd = lcmd->next;
	}
	return (0);
}
