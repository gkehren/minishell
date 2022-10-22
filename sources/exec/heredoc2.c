#include "minishell.h"

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
