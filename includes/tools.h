/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:31:35 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:31:36 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "minishell.h"

/*						TOOLS						*/
void	print_token_lex(t_list *lst);
void	print_cmd(t_list *lst);
void	print_file(t_files *files);

#endif
