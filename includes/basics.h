#ifndef BASICS_H
# define BASICS_H

# include "minishell.h"

/*						BASIC_LIST						*/
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

/*						BASIC_LIST2						*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));

/*						BASIC_STR						*/
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);

#endif