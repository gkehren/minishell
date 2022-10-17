/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:48:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/14 12:45:27 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;
int	stop;

int	main(int argc, char **argv, char **env)
{
	t_list		*venv;
	t_list		*token_list;
	t_list		*cmd;
	
	begin_signal();
	(void)argc;
	(void)argv;
	venv = NULL;
	token_list = NULL;
	cmd = NULL;
	monitor(venv, token_list, cmd, env);
	return (0);
}