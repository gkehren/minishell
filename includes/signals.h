#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/*						SIGNALS						*/
void	handle_sigint(int sig);
void	begin_signal(void);
void	handle_sigint_hevar(int sig);

#endif