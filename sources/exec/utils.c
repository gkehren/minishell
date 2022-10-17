/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:25:54 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/18 00:09:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_tmp(void)
{
	pid_t			pid;
	const char		*path = "/usr/bin/rm";
	char *const		args[] = {"rm", ".270607020399", NULL};

	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (execve(path, args, NULL) == -1)
			return (perror("execve"), 1);
	}
	return (1);
}

int	get_token_id(t_list *ltoken)
{
	t_token_lex	*token;

	if (!ltoken)
		return (6);
	token = (t_token_lex *)ltoken->content;
	if (token->token == WORD)
		return (WORD);
	else if (token->token == PIPE)
		return (PIPE);
	else if (token->token == IN)
		return (IN);
	else if (token->token == OUT)
		return (OUT);
	else if (token->token == IN_HEREDOC)
		return (IN_HEREDOC);
	else if (token->token == OUT_APPEND)
		return (OUT_APPEND);
	return (-1);
}

char	*get_token_content(t_list *lcmd)
{
	t_cmd		*cmd;
	t_list		*ltoken;
	t_token_lex	*token;

	cmd = (t_cmd *)lcmd->content;
	ltoken = (t_list *)cmd->token_files;
	if (!ltoken)
		return (NULL);
	token = (t_token_lex *)ltoken->content;
	return (token->content);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (!needle || !needle[0])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && i + j < len
			&& haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

char	*path_command(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
	{
		if (!env[i])
			return (NULL);
		i++;
	}
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_double_tab((void **)paths), path);
		free(path);
		i++;
	}
	return (free_double_tab((void **)paths), NULL);
}
