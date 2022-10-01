#include "minishell.h"

static int	metachar_analysis(char *entry, int i)
{
	if (entry[i] == entry[i + 1])
	{
		if (entry[i] == '<')
			return (3);
		else if (entry[i] == '>')
			return (4);
	}
	else
	{
		if (entry[i] == '<')
			return (0);
		else if (entry[i] == '|')
			return (1);
		else if (entry[i] == '>')
			return (2);
	}
	return (-1);
}

static int	lexer_monitor(char *entry, int *i, t_list **token_list)
{
	int	analyse;
	int	check;

	check = 0;
	analyse = metachar_analysis(entry, *i);
	if (analyse != -1)
		check = create_spe_token(token_list, analyse);
	else
		check = create_mand_token(token_list, entry, i);
	if (analyse == 3 || analyse == 4)
		(*i) += 2;
	else if (analyse != -1)
		(*i)++;
	if (check)
		return (1);
	return (0);
}

t_list	*generate_token(char *entry)
{
	int			i;
	t_list		*token_list;

	token_list = NULL;
	i = 0;
	while (entry[i])
	{
		while (entry[i] == ' ' || entry[i] == '\t')
			i++;
		if (!entry[i])
			break ;
		if (lexer_monitor(entry, &i, &token_list))
		{
			ft_lstclear(&token_list, &del_token_lex);
			return (NULL);
		}
	}
	return (token_list);
}
