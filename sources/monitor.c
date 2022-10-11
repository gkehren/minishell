#include "minishell.h"

static void	malloc_failed(void)
{
	ft_putstr_fd("Malloc failed !", 2);
	exit(500);
}

void	monitor(t_list *venv, t_list *token_list, t_list *cmd, char **env)
{
	char	*input;

	if (parse_env_data(&venv, env))
		return (malloc_failed());
	while (42)
	{
		input = readline("MINISHELL$>");
		if (ft_strcmp(input, "exit") == 0)
			break ;
		token_list = generate_token(input, 1);
		if (token_list == NULL)
			return (ft_lstclear(&venv, &del_venv), malloc_failed());
		if (expanser(&token_list, venv))
			return (ft_lstclear(&venv, &del_venv), ft_lstclear(&token_list, &del_token_lex), malloc_failed());
		if (parser_checker(&token_list))
			return (ft_lstclear(&venv, &del_venv), ft_lstclear(&token_list, &del_token_lex), exit(2));
		cmd = generate_cmd(token_list);
		if (cmd == NULL)
			return (ft_lstclear(&venv, &del_venv), ft_lstclear(&token_list, &del_token_lex), malloc_failed());
		/* EXEC */
		ft_lstclear(&cmd, &del_cmd);
		free(input);
	}
	ft_lstclear(&venv, del_venv);
}