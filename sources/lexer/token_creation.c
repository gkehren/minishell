#include "minishell.h"

static int	find_quote(char *str, int *i, int *count)
{
	char	tmp;

	tmp = str[*i];
	(*count)++;
	(*i)++;
	while (str[*i] && str[*i] != tmp)
	{
		(*count)++;
		(*i)++;
	}
	if (str[*i] == '\0')
		return (print_error_char(
				"minishell: syntax error near unexpected token `", tmp, "\'\n"));
	(*i)++;
	(*count)++;
	return (0);
}

static int	count_size_word(char *charset, char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (find_quote(str, &i, &count))
				return (-1);
		}
		else
		{
			if (find_char(str[i], charset))
				return (count);
			count++;
			i++;
		}
	}
	return (count);
}

static int	create_token(t_list **token_list, char *content, t_token token)
{
	t_token_lex	*new_content;
	t_list		*new_element;

	new_content = init_token_lex(content, token);
	if (new_content == NULL)
		return (1);
	new_element = ft_lstnew((void *)new_content);
	if (new_element == NULL)
	{
		free(new_content);
		return (1);
	}
	ft_lstadd_back(token_list, new_element);
	return (0);
}

int	create_spe_token(t_list **token_list, int analyse)
{
	const char		*symb[] = {"<", "|", ">", "<<", ">>"};
	const t_token	token_symb[] = {IN, PIPE, OUT, IN_HEREDOC, OUT_APPEND};
	char			*content;
	int				i;

	i = ft_strlen((char *)symb[analyse]);
	content = (char *)malloc(sizeof(char) * (i + 1));
	if (content == NULL)
		return (1);
	ft_strlcpy(content, (char *)symb[analyse], i + 1);
	if (create_token(token_list, content,
			(t_token)token_symb[analyse]))
		return (1);
	return (0);
}

int	create_mand_token(t_list **token_list, char *entry, int *i)
{
	int		count;
	char	*word;
	int		j;

	count = count_size_word(" \t<>|", entry + *i);
	if (count == -1)
		return (1);
	word = (char *)malloc(sizeof(char) * (count + 1));
	if (word == NULL)
		return (1);
	j = 0;
	while (count)
	{
		word[j] = entry[*i];
		j++;
		(*i)++;
		count--;
	}
	word[j] = '\0';
	if (create_token(token_list, word, WORD))
	{
		free(word);
		return (1);
	}
	return (0);
}
