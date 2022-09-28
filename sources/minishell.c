#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_list		*venv;
	t_list		*token_list;

	(void)argc;
	(void)argv;
	venv = NULL;
	if (parse_env_data(&venv, env))
		return (1);
	while (42)
	{
		input = readline("First prompt :");
		token_list = generate_token(input);
		print_token_lex(token_list);
		expanser(token_list, venv);
		ft_lstclear(&token_list, &del_token_lex);
		free(input);
	}
	ft_lstclear(&venv, del_venv);
	return (0);
}

// int	main(void)
// {
// 	printf("%s\n", find_title_expand("HOME{e"));
// 	return (0);
// }