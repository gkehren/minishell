#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*						ENV_TOOLS						*/
int		venv_exist(t_list **venv, char *title);
void	venv_replace(t_list **venv, char *title, char *content);
int		venv_create(t_list **venv, char *title, char *content, t_set set);
void	venv_remove(t_list **venv, char *title);

/*						ENV						*/
char	**send_env(t_list **venv);
void	env(t_list **venv, char **args, int status_ret);

/*						EXPORT						*/


/*						HANDLE_ENV						*/
char	**cut_env(char *env_part);
int		parse_env_data(t_list **venv, char **env);
/*						HANDLE_ENV2						*/
char	**malloc_not_init(char *env_part);
int		malloc_failed_env(t_list **venv);

/*						UNSET						*/
int		unset(t_list **venv, char **args, int status_ret);

#endif