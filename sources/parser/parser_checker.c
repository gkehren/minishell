#include "minishell.h"

int	parser_checker(t_list **token_list)
{
	t_token_lex	*tmp_content;
	t_list		*tmp_list;

	tmp_list = *token_list;
	while (tmp_list)
	{
		tmp_content = (t_token_lex *)tmp_list->content;
		if (tmp_content->token == WORD)
		{
			if (ft_isalnum(tmp_content->content[0]) && tmp_content->content[0] != '_')
				print_error_char("minishell: syntax error near unexpected token `", tmp_content->content[0], "\'\n");
		}
		else if (tmp_content->token == PIPE)
		{
			if (tmp_list == *token_list)
				print_error_char("minishell: syntax error near unexpected token `", tmp_content->content[0], "\'\n");
			else if (tmp_list->next == NULL)
				print_error("minishell: syntax error: unexpected end of file");
		}
		else
		{
			if (tmp_list->next != NULL)
			{
				tmp_content = (t_token_lex *)tmp_list->next->content;

			}
			if (tmp_content->token != WORD)
				print_error_char("minishell: syntax error near unexpected token `", tmp_content->content[0], "\'\n");
		}
		tmp_list = tmp_list->next;
	}
	return (0);
}