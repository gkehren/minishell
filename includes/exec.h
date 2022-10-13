/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:02:44 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/13 11:07:18 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*						EXEC						*/
int			exec(t_list *lcmd, t_list *env);
void		child_process(int *fd, int *fdd, char **env, t_list *lcmd);
void		child_process_out(int *fd, int *fdd, char **env, t_list *lcmd);
void		child_process_in(void);

/*						FILES						*/
void		init_files_cmd(t_list *cmd, t_list *venv);

/*						HEREDOC						*/
t_heredoc	init_heredoc_var(char *stop, int heredoc_ex, t_files *files, int mode);
int			heredoc(t_heredoc heredoc_var, t_list *venv);

/*						UTILS						*/
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*path_command(char *cmd, char **env);
int			get_token_id(t_list *ltoken);
char		*get_token_content(t_list *lcmd);

#endif
