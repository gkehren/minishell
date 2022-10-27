/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:28:52 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:28:52 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_echo(int argc, char **args, t_list **venv, t_exec *exec)
{
	int	i;
	int	check;
	int	option_ok;

	check = 0;
	option_ok = 0;
	i = 0;
	while (args[++i])
	{
		if (check_option(args[i]) && check == 0)
			option_ok = 1;
		else
		{
			check = 1;
			if (args[i + 1] != NULL)
				printf("%s ", args[i]);
			else
				printf("%s", args[i]);
		}
	}
	if (option_ok == 0)
		printf("\n");
	return ((void)exec, (void)argc, (void)venv, set_status(0), 0);
}
