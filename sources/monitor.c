#include "minishell.h"

void	malloc_failed(void)
{
	ft_putstr_fd("minishell: malloc error\n", 2);
	rl_clear_history();
	exit(500);
}

static int	parsing_part(t_list **venv, t_list **token_list, t_list **cmd, char *input)
{
	*token_list = generate_token(input, 1);
	if (*token_list == NULL)
		return (ft_lstclear(token_list, &del_token_lex), 1);
	if (expanser(token_list, *venv, 0))
		return (ft_lstclear(venv, &del_venv), ft_lstclear(token_list, &del_token_lex), malloc_failed(), 1);
	if (parser_checker(token_list))
		return (ft_lstclear(venv, &del_venv), ft_lstclear(token_list, &del_token_lex), 1);
	*cmd = generate_cmd(token_list, venv);
	if (*cmd == NULL)
		return (1);
	return (0);
}

void	monitor(t_list *venv, t_list *token_list, t_list *cmd, char **env)
{
	char	*input;

	if (parse_env_data(&venv, env))
		return (malloc_failed());
	while (42)
	{
		input = readline("MINISHELL$> ");
		if (input == 0)
			return (ft_lstclear(&venv, &del_venv), printf("exit\n"), rl_clear_history(), exit(0));
		add_history(input);
		if (parsing_part(&venv, &token_list, &cmd, input) == 0)
		{
			exec(&cmd, &venv, -2);
			// print_cmd(cmd);
			ft_lstclear(&cmd, &del_cmd);
		}
		free(input);
	}
}
