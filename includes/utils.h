#ifndef UTILS_H
#define UTILS_H

#include "minishell.h"

/*						UTILS						*/
int 		find_char(char c, char *str);
int			save_quote(int booli, char c);
void		set_status(int status);

/*						PRINT_ERROR						*/
int			print_error(char *error);
int			print_error_char(char *error_b, char c, char *error_e);
int			print_error_str(char *error_b, char *content, char *error_e);
void		print_cd_error(char *path, char *strerror);
void		print_nb_error(char *begin, int nb, char *end);

/*						HANDLE_STRUCT						*/
t_token_lex	*init_token_lex(char *content, t_token token);
void 		del_token_lex(void *lst);
t_venv 		*init_venv(char *title, char *content, t_set set);
void 		del_venv(void *lst);
void		del_cmd(void *lst);

/*						CHECK_CHAR						*/
int 		ft_isdigit(int c);
int 		ft_isalpha(int c);
int 		ft_isalnum(int c);
int			good_token(int c);

/*						FREE						*/
void	free_double_tab(void **ptr);

#endif
