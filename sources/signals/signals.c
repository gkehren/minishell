#include "minishell.h"

void	handle_sigint_pro(int sig)
{
	(void)sig;
	printf("\n");
}

void	handle_sigquit_pro(int sig)
{
	(void)sig;
	printf("Quit\n");
}

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
	(void)sig;
	stop = -42;
	write(1, "\n", 1);
	close(0);
}

void	begin_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}