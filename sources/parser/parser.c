#include "minishell.h"

static t_cmd	*init_current_cmd(void)
{
	t_cmd	*current_cmd;

	current_cmd = (t_cmd *)malloc(sizeof(t_cmd *));
	if (current_cmd == NULL)
		return (NULL);
	current_cmd->full_path = NULL;
	current_cmd->full_cmd = NULL;
	current_cmd->token_files = NULL;
	return (current_cmd);
}

static void	process_cmd(t_list **tmp_list, t_cmd *current_cmd)
{

}

static int	add_cmd(t_list **cmd_list, t_cmd *current_cmd)
{
	t_list	*new_cmd;

	new_cmd = ft_lstnew((void *)current_cmd);
	if (new_cmd == NULL)
		return (free(current_cmd), 1);
	ft_lstadd_back(cmd_list, new_cmd);
	current_cmd = init_current_cmd();
	if (current_cmd == NULL)
		return (ft_lstclear(cmd_list, ), 1);
	return (0);
}

t_cmd	*generate_cmd(t_list *token_list)
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
		process_cmd(&tmp_list, current_cmd);
		if (add_cmd(&tmp_list, current_cmd))
			return (NULL);
	}
	return (cmd_list);
}