#include "minishell.h"

static void	insert_word_token(t_list **token_list,
	t_list **current, t_list **prec, t_list *tmp_token)
{
	t_list	*next_one;

	next_one = (*current)->next;
	ft_lstdelone(*current, del_token_lex);
	if (*prec == NULL)
		*token_list = tmp_token;
	else
		(*prec)->next = tmp_token;
	while (tmp_token->next)
		tmp_token = tmp_token->next;
	tmp_token->next = next_one;
	*prec = tmp_token;
	*current = next_one;
}

static void	remove_word_token(t_list **token_list,
	t_list **current, t_list **prec)
{
	t_list	*next_one;

	next_one = (*current)->next;
	if (*prec == NULL)
		*token_list = next_one;
	else
		(*prec)->next = next_one;
	ft_lstdelone(*current, del_token_lex);
	*current = next_one;
}

static int	checker_word(t_list **token_list,
	t_list **current, t_list **prec, char *word)
{
	t_list	*tmp_token;

	tmp_token = NULL;
	if (word[0] == '\0')
		remove_word_token(token_list, current, prec);
	else
	{
		tmp_token = generate_token(word, 0);
		if (tmp_token == NULL)
			return (1);
		turn_to_word(tmp_token);
		insert_word_token(token_list, current, prec, tmp_token);
	}
	return (0);
}

int	clean_expand(t_list **token_list)
{
	t_list		*prec;
	t_list		*tmp_list;
	t_token_lex	*tmp_token;

	tmp_list = *token_list;
	prec = NULL;
	while (tmp_list)
	{
		tmp_token = (t_token_lex *)tmp_list->content;
		if (tmp_token->token == WORD)
		{
			if (checker_word(token_list, &tmp_list, &prec, tmp_token->content))
				return (1);
		}
		else
		{
			prec = tmp_list;
			tmp_list = tmp_list->next;
		}
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
