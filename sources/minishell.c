/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:48:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/10 21:11:12 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_list		*venv;
	t_list		*token_list;
	t_list		*cmd;

	(void)argc;
	(void)argv;
	venv = NULL;
	if (parse_env_data(&venv, env))
		return (1);
	while (42)
	{
		input = readline("Minishell$ ");
		if (ft_strcmp(input, "exit") == 0)
			break ;
		token_list = generate_token(input, 1);
		if (token_list == NULL)
			break ;
		//print_token_lex(token_list);
		expanser(&token_list, venv);
		//print_token_lex(token_list);
		if (parser_checker(&token_list))
			break ;
		cmd = generate_cmd(token_list);
		print_cmd(cmd);
		// if (exec(cmd, venv))
		// 	return (1);
		free(input);
	}
	ft_lstclear(&venv, del_venv);
	return (0);
}
