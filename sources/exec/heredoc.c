#include "minishell.h"

#define EXIT_1 "minishell: warning: here-document at line "
#define EXIT_2 " delimited by end-of-file (wanted `end\')\n"

t_heredoc init_heredoc_var(char *stop, int heredoc_ex, t_files *files, int mode)
{
	t_heredoc	heredoc_var;

	heredoc_var.files = files;
	heredoc_var.heredoc_ex = heredoc_ex;
	heredoc_var.mode = mode;
	heredoc_var.stop = stop;
	return (heredoc_var);
}

static int	expand_heredoc(char *str, t_heredoc hevar, t_list *venv)
{
	t_token_lex	*tmp;

	tmp = init_token_lex(str, WORD);
	if (tmp == NULL)
		return (1);
	if (hevar.heredoc_ex == 0)
		expand_process(tmp, venv, 1);
	// printf("str is equal to %s\n", tmp->content);
	hevar.files->infile = open("tmp", O_CREAT | O_WRONLY);
	printf("fd equal to %d\n", hevar.files->infile);
	hevar.files->title_heredoc = NULL;
	printf("return write : %ld\n", write(hevar.files->infile, "MDR", 3));
	printf("error -> %s\n", strerror(errno));
	// write(hevar.files->infile, "MDR", 3);
	printf("gnl said : %s\n", get_next_line(hevar.files->infile));
	close(hevar.files->infile);
	del_token_lex((void *)tmp);
	return (0);
}

// static void	init_heredoc(t_files *files, int heredoc_ex, char *str)
// {

// }

int	heredoc(t_heredoc hevar, t_list *venv)
{
	char	*result;
	char	*tmp;
	char	*input;
	int		count_line;

	count_line = 1;
	tmp = NULL;
	result = NULL;
	while (42)
	{
		input = readline("> ");
		if (input == 0)
		{
			print_nb_error(EXIT_1, count_line, EXIT_2);
			break;
		}
		if (ft_strcmp(input, hevar.stop) == 0)
			break;
		tmp = result;
		result = ft_strjoin(result, input);
		if (result == NULL)
			return (free(tmp), 1);
		free(tmp);
		count_line++;
	}
	printf("result is equal to %s\n", result);
	if (expand_heredoc(result, hevar, venv))
		return (1);
	return (0);
}