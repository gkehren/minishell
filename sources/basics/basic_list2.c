/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:29:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:29:15 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		ft_lstdelone(current, del);
		current = *lst;
	}
	*lst = NULL;
}
