#include "minishell.h"

#define EXIT_1 "minishell: warning: here-document at line "
#define EXIT_2 " delimited by end-of-file (wanted `end\')\n"

int	heredoc(char *stop)
{
	// char	**result;
	// char	**tmp;
	char	*input;
	int		count_line;

	count_line = 1;
	// result = NULL;
	while (42)
	{
		count_line++;
		input = readline("> ");
		if (input == 0)
			return (print_nb_error(EXIT_1, count_line, EXIT_2), 0);
		if (ft_strcmp(input, stop) == 0)
			break;
	}
	return (0);
}