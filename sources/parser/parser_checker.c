#include "minishell.h"

#define ERROR_MSG "minishell: syntax error near unexpected token `"
#define ERROR_P "minishell: syntax error near unexpected token `|\'\n"
#define ERROR_NL "minishell: syntax error near unexpected token `newline\'\n"
#define ERROR_EL "minishell: syntax error: unexpected end of file\n"

int	core_checker(t_list **token_list, t_token_lex *tmp_content,
	t_list *tmp_list, t_token_lex *tmp_content_next)
{
	if (tmp_content->token == PIPE)
	{
		if (tmp_list == *token_list)
			return (print_error_char(ERROR_MSG, tmp_content->content[0], "\'\n"));
		else if (tmp_list->next == NULL)
			return (print_error(ERROR_EL));
		else if (tmp_content_next->token == PIPE)
			return (print_error(ERROR_P));
	}
	else if (tmp_content->token != WORD)
	{
		if (tmp_list->next == NULL)
			return (print_error(ERROR_NL));
		else
		{
			if (tmp_content_next->token != WORD)
				return (print_error_str(ERROR_MSG,
						tmp_content_next->content, "\'\n"));
		}
	}
	return (0);
}

int	parser_checker(t_list **token_list)
{
	t_token_lex	*tmp_content;
	t_token_lex	*tmp_content_next;
	t_list		*tmp_list;

	tmp_list = *token_list;
	while (tmp_list)
	{
		tmp_content = (t_token_lex *)tmp_list->content;
		if (tmp_list->next != NULL)
			tmp_content_next = (t_token_lex *)tmp_list->next->content;
		if (core_checker(token_list, tmp_content, tmp_list, tmp_content_next))
			return (1);
		tmp_list = tmp_list->next;
	}
	return (0);
}
