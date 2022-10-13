/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:58:21 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/13 18:17:04 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

/*						GENERIC						*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*						BUILTINS						*/
typedef int (*t_builtins)(int, char **, t_list **);

/*						LEXER						*/
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
	int					heredoc_ex;
}		t_token_lex;

/*						ENV						*/
typedef struct s_venv
{
	char			*title;
	char			*content;
	t_set			set;
}		t_venv;

/*						EXPANSER						*/
typedef enum s_ex_mode
{
	REPLACE,
	PASS
}	t_ex_mode;

typedef struct s_expanse
{
	t_ex_mode	mode;
	char		char_to_rem;
}	t_expanse;

/*						FILES						*/
typedef struct s_files
{
	int		infile;
	int		outfile;
}	t_files;

/*						PARSER						*/
typedef struct s_cmd
{
	char		**full_cmd;
	int			argc;
	t_builtins	builtin;
	t_list		*token_files;
	t_files		*files;
}	t_cmd;

/*						HEREDOC						*/
typedef struct s_heredoc
{
	char	*stop;
	int		heredoc_ex;
	t_files	*files;
	int		mode;
}	t_heredoc;

#endif
