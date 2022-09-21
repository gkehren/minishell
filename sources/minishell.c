#include "minishell.h"

int	main(void)
{
	char		*input;
	t_token_lex	*token_list;

	while (42)
	{
		input = readline("First prompt :");
		token_list = generate_token(input);
		print_token_lex(token_list);
		//ft_lstclear_tl(token_list);
		free(input);
	}
	return (0);
}
