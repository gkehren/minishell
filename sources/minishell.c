/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:48:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/19 17:12:01 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

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