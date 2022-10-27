/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_expand2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:30:06 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:30:07 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_booli(int *booli, char c)
{
	if (c == '\"' && *booli == 0)
		*booli = 1;
	else if (c == '\"' && *booli == 1)
		*booli = 0;
	if (c == '\'' && *booli == 0)
		*booli = 2;
	else if (c == '\'' && *booli == 2)
		*booli = 0;
}

static int	count_quotes(char *str)
{
	int	i;
	int	count;
	int	booli;

	booli = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		manage_booli(&booli, str[i]);
		if ((str[i] == '\'' && booli != 1) || (str[i] == '\"' && booli != 2))
			count++;
		i++;
	}
	return (count);
}

static char	*process_clean_quotes(char *str, int i, int j, int booli)
{
	int		size;
	char	*result;

	size = ft_strlen(str) - count_quotes(str) + 1;
	result = (char *)malloc(sizeof(char) * size);
	if (result == NULL)
		return (NULL);
	while (str[i])
	{
		manage_booli(&booli, str[i]);
		if (save_quote(booli, str[i]))
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

static int	clean_tk(t_list *token_list)
{
	t_token_lex	*tmp_token;

	while (token_list)
	{
		tmp_token = (t_token_lex *)token_list->content;
		tmp_token->content = process_clean_quotes(tmp_token->content, 0, 0, 0);
		if (tmp_token->content == NULL)
			return (1);
		token_list = token_list->next;
	}
	return (0);
}

int	clean_quotes_v2(t_list *cmd)
{
	t_cmd	*tmp_cmd;
	int		i;

	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		i = 0;
		while (tmp_cmd->full_cmd && tmp_cmd->full_cmd[i])
		{
			tmp_cmd->full_cmd[i] = process_clean_quotes(tmp_cmd->full_cmd[i],
					0, 0, 0);
			if (tmp_cmd->full_cmd[i] == NULL)
				return (1);
			i++;
		}
		if (clean_tk(tmp_cmd->token_files))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
