#ifndef UTILS_H
#define UTILS_H

#include "minishell.h"

/*						UTILS						*/
int 		find_char(char c, char *str);
int			print_error(char *error);
int			print_error_char(char *error_b, char c, char *error_e);


/*						HANDLE_STRUCT						*/
t_token_lex	*init_token_lex(char *content, t_token token);
void 		del_token_lex(void *lst);
t_venv 		*init_venv(char *title, char *content, t_set set);
void 		del_venv(void *lst);

/*						CHECK_CHAR						*/
int 		ft_isdigit(int c);
int 		ft_isalpha(int c);
int 		ft_isalnum(int c);

#endif