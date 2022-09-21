#ifndef BASICS_H
# define BASICS_H

# include "minishell.h"

/*						BASIC_LIST_GEN						*/
int			ft_lstsize(void *lst);
void		*ft_lstlast(void *lst);
void		ft_lstadd_back(void **bg_lst, void *new);
/*						BASIC_LIST_SPE						*/
t_token_lex	*ft_lstnew_tl(char *content, t_token token);
void		ft_lstdelone_tl(t_token_lex *lst);
void		ft_lstclear_tl(t_token_lex *bg_lst);

#endif