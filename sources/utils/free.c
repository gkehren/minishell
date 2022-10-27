/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:31:02 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:31:02 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_tab(void **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}

void	free_parser(t_list **token_list, t_list **venv, t_list *cmd_list)
{
	ft_lstclear(venv, &del_venv);
	ft_lstclear(token_list, &del_token_lex);
	ft_lstclear(&cmd_list, &del_cmd);
	malloc_failed();
}
