/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:02:44 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/11 19:43:23 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*						EXEC						*/
int		exec(t_list *lcmd, t_list *env);
void	child_process(int *fd, int *fdd, char **env, t_list *lcmd);
void	child_process_out(int *fd, int *fdd, char **env, t_list *lcmd);
void	child_process_in(int *fd, int *fdd, char **env, t_list *lcmd);
void	exec_error(t_list *lcmd, t_list *venv);

/*						UTILS						*/
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*path_command(char *cmd, char **env);
int			get_token_id(t_list *ltoken);
char		*get_token_content(t_list *lcmd);

#endif
