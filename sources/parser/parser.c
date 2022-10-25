#include "minishell.h"

static t_cmd	*init_current_cmd(void)
{
	t_cmd	*current_cmd;

	current_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (current_cmd == NULL)
		return (NULL);
	current_cmd->full_cmd = NULL;
	current_cmd->argc = 0;
	current_cmd->builtin = NULL;
	current_cmd->token_files = NULL;
	return (current_cmd);
}

static int	process_cmd(t_list **tmp_list, t_cmd *current_cmd,
	t_token_lex *tmp_content)
{
	while (*tmp_list)
	{
		tmp_content = (t_token_lex *)(*tmp_list)->content;
		if (tmp_content->token == WORD)
		{
			current_cmd->full_cmd = new_full_cmd(current_cmd->full_cmd,
					tmp_content->content);
			if (current_cmd->full_cmd == NULL)
				return (del_cmd(current_cmd), 1);
		}
		else if (tmp_content->token == PIPE)
			return ((*tmp_list) = (*tmp_list)->next, 0);
		else
		{
			if (new_token_files(&current_cmd->token_files, tmp_content,
					(t_token_lex *)(*tmp_list)->next->content))
				return (1);
		}
		(*tmp_list) = (*tmp_list)->next;
	}
	return (0);
}

static int	add_cmd(t_list **cmd_list, t_cmd **current_cmd, t_list *tmp_list)
{
	t_list	*new_cmd;

	new_cmd = ft_lstnew((void *)(*current_cmd));
	if (new_cmd == NULL)
		return (free(*current_cmd), 1);
	ft_lstadd_back(cmd_list, new_cmd);
	if (tmp_list)
	{
		*current_cmd = init_current_cmd();
		if (*current_cmd == NULL)
			return (ft_lstclear(cmd_list, &del_cmd), 1);
	}
	return (0);
}

static void	init_cmd(t_list **cmd_list, t_list **tmp_list,
	t_cmd **current_cmd, t_list **token_list)
{
	*cmd_list = NULL;
	*tmp_list = *token_list;
	*current_cmd = init_current_cmd();
}

t_list	*generate_cmd(t_list **token_list, t_list **venv)
{
	t_list	*cmd_list;
	t_list	*tmp_list;
	t_cmd	*current_cmd;

	if (!token_list)
		return (NULL);
	init_cmd(&cmd_list, &tmp_list, &current_cmd, token_list);
	if (current_cmd == NULL)
		return (ft_lstclear(token_list, &del_token_lex), NULL);
	while (tmp_list)
	{
		if (process_cmd(&tmp_list, current_cmd, NULL))
			return (free_parser(token_list, venv, cmd_list), NULL);
		if (add_cmd(&cmd_list, &current_cmd, tmp_list))
			return (free_parser(token_list, venv, cmd_list), NULL);
	}
	ft_lstclear(token_list, &del_token_lex);
	if (clean_quotes_v2(cmd_list))
		return (ft_lstclear(venv, &del_venv), ft_lstclear(&cmd_list, &del_cmd),
			malloc_failed(), NULL);
	init_argc_cmd(cmd_list);
	init_builtins_cmd(cmd_list);
	if (init_files_cmd(cmd_list, *venv))
		return (ft_lstclear(&cmd_list, &del_cmd), NULL);
	return (cmd_list);
}
