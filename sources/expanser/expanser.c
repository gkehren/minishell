#include "minishell.h"

static void	set_expanse(t_expanse *expanse, char c)
{
	if (expanse->char_to_rem == 0)
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
		expanse->char_to_rem = REPLACE;
	}
}

static int	init_expand_process(t_expanse *expanse, t_token_lex *token,
	char **tmp, int *i)
{
	expanse->mode = REPLACE;
	expanse->char_to_rem = 0;
	*tmp = ft_strdup(token->content);
	if (tmp == NULL)
		return (1);
	*i = 0;
	return (0);
}

static int	expand_process(t_token_lex	*token, t_list *venv)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	t_expanse	expanse;

	if (init_expand_process(&expanse, token, &tmp, &i))
		return (1);
	tmp2 = token->content;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			set_expanse(&expanse, tmp[i]);
		else if (tmp[i] == '$')
		{
			if (expand_word(expanse, venv, &tmp, i))
				return (1);
			if (tmp[i] == '\0')
				break ;
		}
		i++;
	}
	token->content = tmp;
	free(tmp2);
	return (0);
}

int	expanser(t_list **token_list, t_list *venv)
{
	t_token_lex	*tmp_token;
	t_list		*tmp_list;

	tmp_list = *token_list;
	while (tmp_list)
	{
		tmp_token = (t_token_lex *)tmp_list->content;
		if (tmp_token->token == WORD)
		{
			printf("AVANT = %s\n", tmp_token->content);
			if (expand_process(tmp_token, venv))
			{
				printf("Malloc error !\n");
				return (1);
			}
			printf("APRES = %s\n", tmp_token->content);
		}
		tmp_list = tmp_list->next;
	}
	clean_expand(token_list);
	return (0);
}
