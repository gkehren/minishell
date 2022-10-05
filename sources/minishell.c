#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_list		*venv;
	t_list		*token_list;
	t_list		*cmd;
	//t_venv		*tmp_venv;

	(void)argc;
	(void)argv;
	venv = NULL;
	if (parse_env_data(&venv, env))
		return (1);
	//AFFICHAGE ENV
	// while (venv)
	// {
	// 	tmp_venv = (t_venv *)venv->content;
	// 	printf("title is %s\n", tmp_venv->title);
	// 	venv = venv->next;
	// }
	while (42)
	{
		input = readline("First prompt :");
		if (ft_strcmp(input, "exit") == 0)
			break ;
		token_list = generate_token(input);
		if (token_list == NULL)
			return (1);
		//print_token_lex(token_list);
		expanser(&token_list, venv);
		//print_token_lex(token_list);
		if (parser_checker(&token_list))
			return (1);
		cmd = generate_cmd(token_list);
		print_cmd(cmd);
		ft_lstclear(&token_list, &del_token_lex);
		free(input);
	}
	ft_lstclear(&venv, del_venv);
	return (0);
}

// int	main(void)
// {
// 	char	**args;

// 	args = ft_split("lol mdr xd", ' ');
// 	free_double_tab((void **)args);
// 	return (0);
// }