/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:25:00 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:25:00 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	init_heredoc_var(char *stop, int heredoc_ex,
	t_files *files, int mode)
{
	t_heredoc	heredoc_var;

	heredoc_var.files = files;
	heredoc_var.heredoc_ex = heredoc_ex;
	heredoc_var.mode = mode;
	heredoc_var.stop = stop;
	return (heredoc_var);
}

void	set_up_tmp(t_heredoc *hevar)
{
	char	*index;
	char	pwd[PATH_MAX];
	char	*tmp;

	getcwd(pwd, PATH_MAX);
	tmp = ft_strjoin(pwd, "/.tmp");
	index = ft_itoa(hevar->files->index_cmd);
	hevar->files->index_cmd_str = ft_strjoin(tmp, index);
	free(index);
	free(tmp);
}
