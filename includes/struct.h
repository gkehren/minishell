#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

typedef enum s_token
{
	WORD,
	PIPE,
	IN,
	OUT,
	IN_HEREDOC,
	OUT_APPEND
}		t_token;

typedef struct s_token_lex {
	char		*content;
	t_token		token;
	t_token_lex	*next;
}		t_token_lex;

#endif