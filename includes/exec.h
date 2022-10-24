/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:02:44 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/25 00:42:57 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*						EXEC						*/

int			exec(t_list **lcmd, t_list **venv, int fdd);
int			parent_process(t_exec *exec, t_list *lcmd, int *fdd);
void		child_process(int *fd, int *fdd, t_exec *exec, t_list *lcmd);
void		child_process_builtins(int *fd, int *fdd, t_exec *exec, t_list *lcmd);
int			only_builtins(t_builtins p_builtins, t_cmd *cmd, t_list *venv, t_exec *exec);
void		free_exec(t_list *lcmd, t_list *venv);

/*						FILES						*/
int			init_files_cmd(t_list *cmd, t_list *venv);
/*						FILES2						*/
int			init_infile(t_list *token_list, t_files *files, t_list *venv);
int			init_outfile(t_list *token_list, t_files *files);
/*						FILES3						*/
void		print_error_files(char *error, t_token_lex *tmp_token);
int			set_error_files(char **error, t_token_lex **tmp_token_error, char *errno_str, t_token_lex *tmp_token);

/*						HEREDOC						*/
t_heredoc	init_heredoc_var(char *stop, int heredoc_ex, t_files *files, int mode);
int			heredoc(t_heredoc hevar, t_list *venv, char *result, int temp);
int			delete_tmp(void);
void		set_up_tmp(t_heredoc *hevar);

/*						UTILS						*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*path_command(char *cmd, char **env);
char	*path_exec(char *cmd);
int		check_abs_path(char *cmd);
void	free_child(t_exec *exec, char **env);
int		get_token_id(t_list *ltoken);
char	*get_token_content(t_list *lcmd);
int		is_sort_token_files(t_list *token_files);

#endif
