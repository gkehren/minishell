/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:32:08 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:32:08 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*						LEXER						*/
t_list		*generate_token(char *entry, int mode);

/*						TOKEN_CREATION						*/
int			create_spe_token(t_list **token_list, int analyse);
int			create_mand_token(t_list **token_list, char *entry,
				int *i, int mode);

#endif
