#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

/*						LEXER						*/
t_token_lex	**generate_token(char *entry);

/*						TOKEN_CREATION						*/
int			create_spe_token(t_token_lex *token_list, int analyse);
int			create_mand_token(t_token_lex *token_list, char *entry, int *i);

#endif