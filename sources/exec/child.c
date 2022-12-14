/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:24:26 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:24:27 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_child(t_list *lcmd, t_cmd *cmd, int *fd, int *fdd)
{
	if (cmd->files->infile != -2)
	{
		dup2(cmd->files->infile, STDIN_FILENO);
		close(cmd->files->infile);
	}
	else
		dup2((*fdd), STDIN_FILENO);
	if (cmd->files->outfile != -2)
	{
		dup2(cmd->files->outfile, STDOUT_FILENO);
		close(cmd->files->outfile);
	}
	else
	{
		if (lcmd->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
	}
	if (*fdd != -2)
		close(*fdd);
	close(fd[0]);
	close(fd[1]);
}

static void	close_fd(int *fdd, t_cmd *cmd)
{
	if (*fdd != -2)
		close(*fdd);
	if (cmd->files->outfile != -2)
		close(cmd->files->outfile);
	if (cmd->files->infile != -2)
		close(cmd->files->infile);
}

static char	*child_process_path(t_cmd *cmd, t_exec *exec, int *fd, char **env)
{
	char	*path;

	if (!cmd->full_cmd)
		return (close_fd(exec->fdd, cmd), close(fd[1]), close(fd[0]),
			free_child(exec, env), exit(1), NULL);
	if (cmd->full_cmd[0][0] == '/' ||
		(cmd->full_cmd[0][0] == '.' && cmd->full_cmd[0][1] == '/'))
	{
		path = path_exec(cmd->full_cmd[0]);
		if (!path)
			return (close_fd(exec->fdd, cmd), close(fd[1]), close(fd[0]),
				free(path), free_child(exec, env), exit(126), NULL);
	}
	else
	{
		path = path_command(cmd->full_cmd[0], env);
		if (!path)
			return (close_fd(exec->fdd, cmd), free(path), close(fd[1]),
				close(fd[0]), free_child(exec, env), exit(127), NULL);
	}
	return (ft_strdup(path));
}

void	child_process(int *fd, int *fdd, t_exec *exec, t_list *lcmd)
{
	t_cmd	*cmd;
	char	*path;
	char	**env;

	cmd = (t_cmd *)lcmd->content;
	exec->fdd = fdd;
	if (cmd->files->is_heredoc == 1)
		free(cmd->files->index_cmd_str);
	env = send_env(exec->venv);
	if (!cmd->full_cmd)
		return (close_fd(exec->fdd, cmd), close(fd[1]), close(fd[0]),
			free_child(exec, env), exit(1));
	path = child_process_path(cmd, exec, fd, env);
	redirect_child(lcmd, cmd, fd, fdd);
	if (execve(path, cmd->full_cmd, env) == -1)
	{
		if (*fdd != -2)
			close(*fdd);
		return (perror("minishell"), free(path),
			free_child(exec, env), exit(1));
	}
}

void	child_process_builtins(int *fd, int *fdd, t_exec *exec, t_list *lcmd)
{
	t_cmd		*cmd;
	t_builtins	builtins;

	cmd = (t_cmd *)lcmd->content;
	if (cmd->files->is_heredoc == 1)
		free(cmd->files->index_cmd_str);
	builtins = (t_builtins)cmd->builtin;
	redirect_child(lcmd, cmd, fd, fdd);
	if (ft_strcmp(cmd->full_cmd[0], "exit") == 0
		|| ft_strcmp(cmd->full_cmd[0], "export") == 0
		|| ft_strcmp(cmd->full_cmd[0], "env") == 0)
	{
		close_builtins(cmd, 0, 0);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	(*builtins)(cmd->argc, cmd->full_cmd, exec->venv, exec);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_lstclear(exec->cmd, &del_cmd);
	ft_lstclear(exec->venv, &del_venv);
	exit(0);
}
