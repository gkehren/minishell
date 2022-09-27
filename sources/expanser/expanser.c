#include "minishell.h"

// static void	set_expanse(t_expanse *expanse, char c)
// {
// 	if (expanse->char_to_rem == 0)
// 	{
// 		expanse->char_to_rem = c;
// 		if (c == '\'')
// 			expanse->mode = PASS;
// 		else
// 			expanse->mode = REPLACE;
// 	}
// 	else if (expanse->char_to_rem == c)
// 	{
// 		expanse->char_to_rem = 0;
// 		expanse->char_to_rem = REPLACE;
// 	}
// }

// static int	expand_process(t_token_lex	*token, t_list *venv)
// {
// 	int			i;
// 	char		*tmp;
// 	t_expanse	expanse;

// 	expanse.mode = REPLACE;
// 	expanse.char_to_rem = 0;
// 	tmp = ft_strdup(token->content);
// 	if (tmp == NULL)
// 		return (1);
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '\'' || tmp[i] == '\"')
// 			set_expanse(&expanse, tmp[i]);
// 		// if (tmp[i] == '$')
// 		// 	expand_word(expanse, venv);
// 		i++;
// 	}
// 	return (0);
// }

int	expanser(t_list *token_list)
{
	t_token_lex	*tmp_token;

	while (token_list)
	{
		tmp_token = (t_token_lex *)token_list->content;
		if (tmp_token->token == WORD)
			//launch_func;
		token_list = token_list->next;
	}
	return (0);
}