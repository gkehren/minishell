#include "minishell.h"

static int	count_quotes(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

static char	*process_clean_quotes(char *str)
{
	int		size;
	int		i;
	int		j;
	char	*result;

	size = ft_strlen(str) - count_quotes(str) + 1;
	result = (char *)malloc(sizeof(char) * size);
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
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
		tmp_token->content = process_clean_quotes(tmp_token->content);
		if (tmp_token->content == NULL)
			return (1);
		token_list = token_list->next;
	}
	return (0);
}

int clean_quotes_v2(t_list *cmd)
{
	t_cmd	*tmp_cmd;
	int		i;

	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		i = 0;
		while (tmp_cmd->full_cmd && tmp_cmd->full_cmd[i])
		{
			tmp_cmd->full_cmd[i] = process_clean_quotes(tmp_cmd->full_cmd[i]);
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

void	turn_to_word(t_list *token_list)
{
	t_token_lex	*tmp_content;

	while (token_list)
	{
		tmp_content = (t_token_lex *)token_list->content;
		tmp_content->token = WORD;
		token_list = token_list->next;
	}
}
