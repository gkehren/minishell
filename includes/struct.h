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

typedef enum s_set
{
	INIT,
	NOT_INIT
}	t_set;

typedef struct s_token_lex 
{
	struct s_token_lex	*next;
	char				*content;
	t_token	token;
}		t_token_lex;

typedef struct s_venv
{
	struct s_venv	*next;
	char			*title;
	char			*content;
	t_set			set;
}		t_venv;

#endif