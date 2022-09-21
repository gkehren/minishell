#include "minishell.h"

int	main(void)
{
	char		*input;
	t_list		*token_list;

	while (42)
	{
		input = readline("First prompt :");
		token_list = generate_token(input);
		print_token_lex(token_list);
		ft_lstclear(&token_list, &del_token_lex);
		free(input);
	}
	return (0);
}
