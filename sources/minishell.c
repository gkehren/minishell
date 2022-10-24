/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:48:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/24 23:51:58 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **env)
{
	t_list		*venv;
	t_list		*token_list;
	t_list		*cmd;
	
	if (argc != 1)
	{
		ft_putstr_fd("Wrong number of arguments !\n", 2);
		return (1);
	}
	g_global.stop = 1;
	begin_signal();
	(void)argv;
	venv = NULL;
	token_list = NULL;
	cmd = NULL;
	monitor(venv, token_list, cmd, env);
	return (0);
}