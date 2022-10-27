/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:32:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:32:15 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

/*						FREE						*/
void	ft_free(void **ptr);
void	free_parser(t_list **token_list, t_list **venv, t_list *cmd_list);

#endif
