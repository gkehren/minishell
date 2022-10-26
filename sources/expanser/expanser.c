#include "minishell.h"

static void	set_expanse(t_expanse *expanse, char c, int heredoc)
{
	if (heredoc == 1)
		expanse->mode = REPLACE;
	else if (expanse->char_to_rem == 0)
	{
		expanse->char_to_rem = c;
		if (c == '\'')
			expanse->mode = PASS;
		else
			expanse->mode = REPLACE;
	}
	else if (expanse->char_to_rem == c)
	{
		expanse->char_to_rem = 0;
		expanse->mode = REPLACE;
	}
}

static int	init_expand_process(t_expanse *expanse, t_token_lex *token,
	char **tmp, char **tmp2)
{
	expanse->mode = REPLACE;
	expanse->char_to_rem = 0;
	*tmp = ft_strdup(token->content);
	*tmp2 = token->content;
	if (tmp == NULL)
		return (1);
	return (0);
}

int	expand_process(t_token_lex	*token, t_list *venv, int heredoc, int i)
{
	char		*tmp;
	char		*tmp2;
	t_expanse	expanse;

	if (init_expand_process(&expanse, token, &tmp, &tmp2))
		return (1);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			set_expanse(&expanse, tmp[i++], heredoc);
		else if (tmp[i] == '$')
		{
			if (expand_word(expanse, venv, &tmp, &i))
				return (1);
			if (tmp[i] == '\0')
				break ;
		}
		else
			i++;
	}
	token->content = tmp;
	free(tmp2);
	return (0);
}

int	expanser(t_list **token_list, t_list *venv, int heredoc)
{
	t_token_lex	*tmp_token;
	t_list		*tmp_list;
	int			booli;

	booli = 0;
	tmp_list = *token_list;
	while (tmp_list)
	{
		tmp_token = (t_token_lex *)tmp_list->content;
		if (tmp_token->token == WORD && booli != 1)
		{
			if (expand_process(tmp_token, venv, heredoc, 0))
				return (1);
		}
		if (tmp_token->token == IN_HEREDOC)
			booli = 1;
		else
			booli = 0;
		tmp_list = tmp_list->next;
	}
	if (clean_expand(token_list))
		return (1);
	return (0);
}
