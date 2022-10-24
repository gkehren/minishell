/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:25:54 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/24 22:50:05 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_sort_token_files(t_list *token_files)
{
	int			booli;
	t_token_lex	*tmp_token;

	booli = 0;
	while (token_files)
	{
		tmp_token = (t_token_lex *)token_files->content;
		if (tmp_token->token == OUT || tmp_token->token == OUT_APPEND)
			booli = 1;
		if ((tmp_token->token == IN && booli == 1)
			|| (tmp_token->token == IN_HEREDOC && booli == 1))
			return (1);
		token_files = token_files->next;
	}
	return (0);
}

void	free_child(t_exec *exec, char **env)
{
	free_double_tab((void *)env);
	ft_lstclear(exec->venv, &del_venv);
	ft_lstclear(exec->cmd, &del_cmd);
}
