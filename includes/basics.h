#ifndef BASICS_H
# define BASICS_H

# include "minishell.h"

/*						BASIC_LIST						*/
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);

/*						BASIC_LIST2						*/
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));

/*						BASIC_STR						*/
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlcpy(char *dst, char *src, int dstsize);

/*						BASIC_STR2						*/
char		*ft_strdup(char *s);
long long	ft_atoi(char *str);
long long	ft_atoll(const char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);

/*						FT_SPLIT						*/
char		**ft_split(char *s, char c);

/*						FT_ITOA						*/
char		*ft_itoa(long long n);

/*						GET_NEXT_LINE						*/
void		*ft_calloc(size_t count, size_t size);
void		ft_substr(char *s, unsigned int start, char *save);
char		*ft_subuff(char *buff, int id_line);
char		*get_next_line(int fd);

#endif
