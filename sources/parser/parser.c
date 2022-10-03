#include "minishell.h"

// static t_cmd	*init_current_cmd(void)
// {
// 	t_cmd	*current_cmd;

// 	current_cmd = (t_cmd *)malloc(sizeof(t_cmd *));
// 	if (current_cmd == NULL)
// 		return (NULL);
// 	current_cmd->full_path = NULL;
// 	current_cmd->full_cmd = NULL;
// 	current_cmd->files = NULL;
// 	return (current_cmd);
// }

// t_cmd	*generate_cmd(t_list *token_list)
// {
// 	t_list	*cmd_list;
// 	t_list	*tmp_list;
// 	t_list	*tmp_token;
// 	t_cmd	*current_cmd;

// 	cmd_list = NULL;
// 	tmp_list = token_list;
// 	current_cmd = init_current_cmd();
// 	while (tmp_list)
// 	{
// 		tmp_token = (t_token_lex *)tmp_list->content;
// 		if (tmp_token ->content == PIPE)
			
// 		tmp_list = tmp_list->next;
// 	}
// 	return (cmd_list);
// }