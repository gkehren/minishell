/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:31:56 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:31:56 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "minishell.h"

void	malloc_failed(void);
void	monitor(t_list *venv, t_list *token_list, t_list *cmd, char **env);

#endif
