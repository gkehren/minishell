#include "minishell.h"

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
		if (tmp_content->token == PIPE)
		{
			if (tmp_list == *token_list)
				return (print_error_char("minishell: syntax error near unexpected token `", tmp_content->content[0], "\'\n"));
			else if (tmp_list->next == NULL)
				return (print_error("minishell: syntax error: unexpected end of file\n"));
			else if (tmp_content_next->token == PIPE)
				return (print_error("minishell: syntax error near unexpected token `|\'\n"));
		}
		else if (tmp_content->token != WORD)
		{
			if (tmp_list->next == NULL)
				return (print_error("minishell: syntax error near unexpected token `newline\'\n"));
			else
			{
				if (tmp_content_next->token != WORD)
					return (print_error_str("minishell: syntax error near unexpected token `", tmp_content->content, "\'\n"));
			}
		}
		tmp_list = tmp_list->next;
	}
	return (0);
}