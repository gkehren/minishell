#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*						UTILS						*/
int			ft_strlen(char *str);
int			find_char(char c, char *str);

/*						HANDLE_STRUCT						*/
t_token_lex	*init_token_lex(char *content, t_token token);
void		del_token_lex(void *lst);
t_venv		*init_venv(char *title, char *content, t_set set);
void		del_venv(void *lst);

#endif