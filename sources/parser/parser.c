#include "minishell.h"

static t_cmd	*init_current_cmd(void)
{
	t_cmd	*current_cmd;

	current_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (current_cmd == NULL)
		return (NULL);
	current_cmd->full_path = NULL;
	current_cmd->full_cmd = NULL;
	current_cmd->token_files = NULL;
	return (current_cmd);
}

static int	process_cmd(t_list **tmp_list, t_cmd *current_cmd)
{
	t_token_lex	*tmp_content;

	while (*tmp_list)
	{
		tmp_content = (t_token_lex *)(*tmp_list)->content;
		if (tmp_content->token == WORD)
		{
			current_cmd->full_cmd = new_full_cmd(current_cmd->full_cmd, tmp_content->content);
			if (current_cmd->full_cmd == NULL)
				return (del_cmd(current_cmd), 1);
			(*tmp_list) = (*tmp_list)->next;
		}
		else if (tmp_content->token == PIPE)
		{
			(*tmp_list) = (*tmp_list)->next;
			return (0);
		}
		else
		{
			if (new_token_files(&current_cmd->token_files, tmp_content, (t_token_lex *)(*tmp_list)->next->content))
				return (1);
			(*tmp_list) = (*tmp_list)->next->next;
		}
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

t_list	*generate_cmd(t_list *token_list)
{
	t_list	*cmd_list;
	t_list	*tmp_list;
	t_cmd	*current_cmd;

	cmd_list = NULL;
	tmp_list = token_list;
	current_cmd = init_current_cmd();
	if (current_cmd == NULL)
		return (NULL);
	while (tmp_list)
	{
		if (process_cmd(&tmp_list, current_cmd))
			return (NULL);
		if (add_cmd(&cmd_list, &current_cmd, tmp_list))
			return (NULL);
	}
	ft_lstclear(&token_list, &del_token_lex);
	return (cmd_list);
}