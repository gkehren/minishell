#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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
	char				*content;
	t_token				token;
}		t_token_lex;

typedef struct s_venv
{
	char			*title;
	char			*content;
	t_set			set;
}		t_venv;

#endif