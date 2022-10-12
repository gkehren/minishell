#ifndef EXPANSER_H
# define EXPANSER_H

#include "minishell.h"

/*						EXPANSER						*/
int		expanser(t_list **token_list, t_list *venv);

/*						EXPAND_WORD						*/
int		expand_word(t_expanse expanse, t_list *venv, char **str, int i);
/*						EXPAND_WORD2						*/
int		expand_return_value(char **expand, char **str);

/*						CLEAN_EXPAND						*/
int		clean_expand(t_list **token_list);
/*						CLEAN_EXPAND2						*/
int 	clean_quotes_v2(t_list *cmd);
void	turn_to_word(t_list *token_list);

#endif