#include "minishell.h"

#define EXIT_1 "minishell: warning: here-document at line "
#define EXIT_2 " delimited by end-of-file (wanted `end\')\n"

static int	expand_heredoc(char *str, t_heredoc hevar, t_list *venv)
{
	t_token_lex	*tmp;

	set_up_tmp(&hevar);
	tmp = init_token_lex(str, WORD);
	if (tmp == NULL)
		return (1);
	if (hevar.heredoc_ex == 0)
	{
		if (expand_process(tmp, venv, 1, 0))
			return (del_token_lex((void *)tmp), 1);
	}
	hevar.files->infile = open(hevar.files->index_cmd_str,
			O_CREAT | O_WRONLY, 0777);
	if (hevar.files->infile == -1)
		return (del_token_lex((void *)tmp), 1);
	if (str)
		write(hevar.files->infile, tmp->content, ft_strlen(tmp->content));
	close(hevar.files->infile);
	hevar.files->infile = open(hevar.files->index_cmd_str, O_RDONLY);
	del_token_lex((void *)tmp);
	if (hevar.files->infile == -1)
		return (1);
	hevar.files->is_heredoc = 1;
	return (0);
}

static char	*process_heredoc(char *input, char *current)
{
	char	*tmp;
	char	*result;

	tmp = input;
	input = ft_strjoin(input, "\n");
	if (input == NULL)
		return (free(input), free(current), NULL);
	free(tmp);
	tmp = current;
	result = ft_strjoin(current, input);
	if (result == NULL)
		return (free(input), free(current), NULL);
	free(input);
	free(tmp);
	return (result);
}

static void	begin_heredoc(char **result)
{
	g_global.stop = 2;
	*result = NULL;
	signal(SIGINT, handle_sigint_hevar);
}

static int	for_one_line(char **result, char *input, int temp)
{
	*result = process_heredoc(input, *result);
	if (*result == NULL)
		return (close(temp), 1);
	return (0);
}

int	heredoc(t_heredoc hevar, t_list *venv, char *result, int temp)
{
	char	*input;

	begin_heredoc(&result);
	while (42)
	{
		input = readline("> ");
		if (input == 0)
		{
			if (g_global.stop == -42)
				return (g_global.stop = 2, signal(SIGINT, handle_sigint),
					dup2(temp, STDIN_FILENO), close(temp),
					free(result), free(input), 1);
			write(1, "\n", 1);
			break ;
		}
		if (ft_strcmp(input, hevar.stop) == 0)
			break ;
		for_one_line(&result, input, temp);
	}
	if (hevar.mode == 0)
		return (free(result), free(input), 0);
	if (expand_heredoc(result, hevar, venv))
		return (close(temp), free(input), 1);
	return (close(temp), free(input), 0);
}
