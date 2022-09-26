#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	//char		*input;
	t_list		*venv;
	//t_list		*token_list;
	char		**args;

	(void)argc;
	(void)argv;
	venv = NULL;
	if (parse_env_data(&venv, env))
		return (1);
	args = ft_split("export", 'c');
	export(&venv, args, 0);
	ft_lstclear(&venv, del_venv);
	/* while (42)
	{
		input = readline("First prompt :");
		token_list = generate_token(input);
		print_token_lex(token_list);
		ft_lstclear(&token_list, &del_token_lex);
		free(input);
	} */
	return (0);
}

/* int	main(void)
{
	printf("%d\n", ft_strcmp("", NULL));
	return (0);
} */