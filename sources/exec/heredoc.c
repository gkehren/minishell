#include "minishell.h"

#define EXIT_1 "minishell: warning: here-document at line "
#define EXIT_2 " delimited by end-of-file (wanted `end\')\n"

t_heredoc	init_heredoc_var(char *stop, int heredoc_ex,
	t_files *files, int mode)
{
	t_heredoc	heredoc_var;

	heredoc_var.files = files;
	heredoc_var.heredoc_ex = heredoc_ex;
	heredoc_var.mode = mode;
	heredoc_var.stop = stop;
	return (heredoc_var);
}

static void	set_up_tmp(t_heredoc *hevar)
{
	char	*index;
	char	pwd[PATH_MAX];
	char	*tmp;

	getcwd(pwd, PATH_MAX);
	tmp = ft_strjoin(pwd, "/.tmp");
	index = ft_itoa(hevar->files->index_cmd);
	hevar->files->index_cmd_str = ft_strjoin(tmp, index);
	free(index);
	free(tmp);
}

static int	expand_heredoc(char *str, t_heredoc hevar, t_list *venv)
{
	t_token_lex	*tmp;

	set_up_tmp(&hevar);
	tmp = init_token_lex(str, WORD);
	if (tmp == NULL)
		return (1);
	if (hevar.heredoc_ex == 0)
	{
		if (expand_process(tmp, venv, 1))
			return (del_token_lex((void *)tmp), 1);
	}
	hevar.files->infile = open(hevar.files->index_cmd_str, O_CREAT | O_WRONLY, 0777);
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
			{
				g_global.stop = 2;
				return (signal(SIGINT, handle_sigint), dup2(temp, STDIN_FILENO),
					close(temp), free(result), free(input), 1);
			}
			break ;
		}
		if (ft_strcmp(input, hevar.stop) == 0)
			break ;
		result = process_heredoc(input, result);
		if (result == NULL)
			return (close(temp), 1);
	}
	free(input);
	if (expand_heredoc(result, hevar, venv))
		return (close(temp), 1);
	return (close(temp), 0);
}
