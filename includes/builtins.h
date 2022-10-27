/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:32:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:32:27 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*						ENV_TOOLS						*/
int		venv_exist(t_list **venv, char *title);
char	*venv_find_content(t_list **venv, char *title);
void	venv_replace(t_list **venv, char *title, char *content);
int		venv_create(t_list **venv, char *title, char *content, t_set set);
void	venv_remove(t_list **venv, char *title);

/*						ENV						*/
char	**send_env(t_list **venv);
int		ft_env(int argc, char **args, t_list **venv, t_exec *exec);

/*						EXPORT						*/
int		ft_export(int argc, char **args, t_list **venv, t_exec *exec);

/*						HANDLE_ENV						*/
char	**cut_env(char *env_part);
int		parse_env_data(t_list **venv, char **env);
/*						HANDLE_ENV2						*/
char	**malloc_not_init(char *env_part);
int		malloc_failed_env(t_list **venv);
int		export_concat(t_list **venv, char *title_env, char **new_content);
int		init_env_i(t_list **venv, char **args);

/*						PARSING_EXPORT					*/
int		parsing_export(char *str);
int		parsing_str_export(char *str);
int		check_char_export(char c, int mode);

/*						UNSET						*/
int		ft_unset(int argc, char **args, t_list **venv, t_exec *exec);
int		error_before(char **args);

/*						PWD						*/
int		ft_pwd(int argc, char **args, t_list **venv, t_exec *exec);

/*						CD						*/
int		ft_cd(int argc, char **args, t_list **venv, t_exec *exec);

/*						ECHO						*/
int		ft_echo(int argc, char **argv, t_list **venv, t_exec *exec);

/*						EXIT						*/
int		ft_exit(int argc, char **args, t_list **venv, t_exec *exec);

#endif
