#ifndef EXPANSER_H
# define EXPANSER_H

#include "minishell.h"

/*						EXPANSER						*/
int		expanser(t_list *token_list, t_list *venv);

/*						EXPAND_WORD						*/
int		expand_word(t_expanse expanse, t_list *venv, char *str, int i);
char	*find_title_expand(char *str);

#endif