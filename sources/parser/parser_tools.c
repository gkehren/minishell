#include "minishell.h"

char	**new_full_cmd(char **full_cmd, char *cmd)
{
	int		size;
	int		i;
	char	**result;

	size = 0;
	while (full_cmd && full_cmd[size])
		size++;
	result = (char **)malloc(sizeof(char *) * (size + 2));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (size)
	{
		result[i] = ft_strdup(full_cmd[i]);
		if (result[i] == NULL)
			return (free_double_tab((void **)result), NULL);
		i++;
		size--;
	}
	result[i] = ft_strdup(cmd);
	if (result[i] == NULL)
		return (free_double_tab((void **)result), NULL);
	result[i + 1] = NULL;
	if (full_cmd)
		free_double_tab((void **)full_cmd);
	return (result);
}

int	new_token_files(t_list **token_files, t_token_lex *token_redir, t_token_lex *token_word)
{
	t_token_lex	*new_file;
	t_list		*new_element;
	char		*tmp;

	tmp = ft_strdup(token_word->content);
	if (tmp == NULL)
		return (1);
	new_file = init_token_lex(tmp, token_redir->token);
	if (new_file == NULL)
		return (free(tmp), 1);
	if (new_file->token == IN_HEREDOC && (find_char('\"', tmp) || find_char('\'', tmp)))
		new_file->heredoc_ex = 1;
	new_element = ft_lstnew((void *)new_file);
	if (new_element == NULL)
		return (del_token_lex(new_file), 1);
	ft_lstadd_back(token_files, new_element);
	return (0);
}

static int	count_argc(char **full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd && full_cmd[i])
		i++;
	return (i);
}

void	init_argc_cmd(t_list *cmd)
{
	t_cmd	*tmp_cmd;
	
	while (cmd)
	{
		tmp_cmd = (t_cmd *)cmd->content;
		tmp_cmd->argc = count_argc(tmp_cmd->full_cmd);
		cmd = cmd->next;
	}
}