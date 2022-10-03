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

int	clean_quotes(t_list **token_list)
{
	t_list		*tmp_list;
	t_token_lex	*tmp_token;

	tmp_list = *token_list;
	while (tmp_list)
	{
		tmp_token = (t_token_lex *)tmp_list->content;
		if (tmp_token->token == WORD)
		{
			tmp_token->content = process_clean_quotes(tmp_token->content);
			if (tmp_token->content == NULL)
				return (1);
		}
		tmp_list = tmp_list->next;
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
