#include "minishell.h"

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
		ft_free((void **)&new_content);
		return (1);
	}
	ft_lstadd_back(token_list, new_element);
	return (0);
}

int	create_spe_token(t_list **token_list, int analyse)
{
	const char* symb[] = {"<", "|", ">", "<<", ">>"};
	const t_token token_symb[] = {IN, PIPE, OUT , IN_HEREDOC, OUT_APPEND};

	if (create_token(token_list, (char *)symb[analyse], (t_token)token_symb[analyse]))
		return (1);
	return (0);
}

int	create_mand_token(t_list **token_list, char *entry, int *i)
{
	int		count;
	char	*word;
	int		j;

	count = count_charset(" \t", entry + *i);
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
		ft_free((void **)&word);
		return (1);
	}
	return (0);
}