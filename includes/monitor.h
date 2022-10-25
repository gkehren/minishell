#ifndef MONITOR_H
# define MONITOR_H

# include "minishell.h"

void	malloc_failed(void);
void	monitor(t_list *venv, t_list *token_list, t_list *cmd, char **env);

#endif
