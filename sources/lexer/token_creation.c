#include "minishell.h"

static int	create_token(t_token_lex *token_list, char *content, t_token token)
{
	t_token_lex	*new;

	new = ft_lstnew_tl(content, token);
	if (new == NULL)
		return (1);
	ft_lstadd_back((void **)&token_list, new);
	return (0);
}

int	create_spe_token(t_token_lex *token_list, int analyse)
{
	int check;
	const char* symb[] = {"<", "|", ">", "<<", ">>"};
	const t_token token_symb[] = {IN, PIPE, OUT , IN_HEREDOC, OUT_APPEND};

	check = 0;
	check = create_token(token_list, (char *)symb[analyse], (t_token)token_symb[analyse]);
	if (check)
		return (1);
	return (0);
}

int	create_mand_token(t_token_lex *token_list, char *entry, int *i)
{
	int		count;
	char	*word;
	int		j;

	(void)token_list;
	count = count_charset(" \t", entry);
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
	printf("word is %s\n", word);
	return (0);
}