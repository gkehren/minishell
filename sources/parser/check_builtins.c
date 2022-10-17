#include "minishell.h"

static t_builtins	check_builtins(t_cmd *cmd)
{
	const char			*str[] = {"export", "echo", "cd",
		"pwd", "unset", "env", "exit", NULL};
	const t_builtins	tab_b[] = {&ft_export, &ft_echo,
		&ft_cd, &ft_pwd, &ft_unset, &ft_env, &ft_exit};
	int					i;

	i = 0;
	while (str[i] && cmd->full_cmd)
	{
		if (strcmp(cmd->full_cmd[0], str[i]) == 0)
			break ;
		i++;
	}
	if (str[i] == NULL)
		return (NULL);
	else
		return (tab_b[i]);
}

void	init_builtins_cmd(t_list *cmd)
{
	t_cmd	*tmp_cmd;

	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		tmp_cmd->builtin = check_builtins(tmp_cmd);
		cmd = cmd->next;
	}
}