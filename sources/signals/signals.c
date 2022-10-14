#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_hevar(int sig)
{
	// int	pipefd[2];

	(void)sig;
	stop = -42;
	write(1, "> ^C\n", 5);
	close(0);
	// if (pipe(pipefd) < 0)
	// 	perror("Pipe :");
	// dup2(pipefd[0], STDIN_FILENO);
	// write(pipefd[1], "\n\n", 2);
	// close(pipefd[0]);
	// close(pipefd[1]);
}

void	begin_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}