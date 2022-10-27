/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:31:44 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:31:45 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/*						SIGNALS						*/
void	handle_sigint(int sig);
void	begin_signal(void);
void	handle_sigint_hevar(int sig);
void	handle_sigint_pro(int sig);
void	handle_sigquit_pro(int sig);

#endif
