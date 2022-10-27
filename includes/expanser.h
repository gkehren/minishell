/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:32:19 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:32:19 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSER_H
# define EXPANSER_H

# include "minishell.h"

/*						EXPANSER						*/
int		expand_process(t_token_lex	*token, t_list *venv, int heredoc, int i);
int		expanser(t_list **token_list, t_list *venv, int heredoc);

/*						EXPAND_WORD						*/
int		expand_word(t_expanse expanse, t_list *venv, char **str, int *i);
/*						EXPAND_WORD2						*/
int		expand_return_value(char **expand, char **str);
void	init_begin(int *j, int i, char *begin, char *str);
void	set_incr_expand(int *i, char c, t_expanse *expanse);
int		check_weird_expand(char *str);

/*						CLEAN_EXPAND						*/
int		clean_expand(t_list **token_list);
/*						CLEAN_EXPAND2						*/
int		clean_quotes_v2(t_list *cmd);
void	turn_to_word(t_list *token_list);
void	manage_booli(int *booli, char c);

#endif
