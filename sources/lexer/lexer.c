#include "minishell.h"

static int	metachar_analysis(char *entry, int i)
{
	if (entry[i] == entry[i + 1] && entry[i] != '|')
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

static int	lexer_monitor(char *entry, int *i, t_list **token_list, int mode)
{
	int	analyse;
	int	check;

	check = 0;
	analyse = metachar_analysis(entry, *i);
	if (analyse != -1)
		check = create_spe_token(token_list, analyse);
	else
		check = create_mand_token(token_list, entry, i, mode);
	if (analyse == 3 || analyse == 4)
		(*i) += 2;
	else if (analyse != -1)
		(*i)++;
	if (check)
		return (1);
	return (0);
}

static int	check_token_word(t_list *token_list)
{
	t_token_lex	*tmp_content;

	while (token_list)
	{
		tmp_content = (t_token_lex *)token_list->content;
		if (tmp_content->token == WORD)
		{
			if (!ft_isalnum(tmp_content->content[0])
				&& !good_token(tmp_content->content[0]))
				return (print_error_char
					("minishell: syntax error near unexpected token `",
						tmp_content->content[0], "\'\n"));
		}
		token_list = token_list->next;
	}
	return (0);
}

t_list	*generate_token(char *entry, int mode)
{
	int			i;
	t_list		*token_list;
	int			check;

	token_list = NULL;
	i = 0;
	while (entry && entry[i])
	{
		while (entry[i] == ' ' || entry[i] == '\t')
			i++;
		if (!entry[i])
			break ;
		check = lexer_monitor(entry, &i, &token_list, mode);
		if (check == 1)
			return (ft_lstclear(&token_list, &del_token_lex), NULL);
	}
	if (mode == 1)
	{
		if (check_token_word(token_list))
			return (ft_lstclear(&token_list, &del_token_lex), NULL);
	}
	return (token_list);
}
