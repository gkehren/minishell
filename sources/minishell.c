/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:48:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/26 01:34:20 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **env)
{
	t_list		*venv;
	t_list		*token_list;
	t_list		*cmd;

	(void)argv;
	g_global.stop = 1;
	venv = NULL;
	token_list = NULL;
	cmd = NULL;
	if (argc != 1)
	{
		ft_putstr_fd("Wrong number of arguments !\n", 2);
		return (1);
	}
	if (env[0] == NULL)
	{
		if (init_env_i(&venv, NULL) == 1)
			return (ft_putstr_fd("minishell: init error\n", 2), 1);
	}
	begin_signal();
	monitor(venv, token_list, cmd, env);
	return (0);
}
