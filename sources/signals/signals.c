#include "minishell.h"

void	handle_sigint_pro(int sig)
{
	(void)sig;
	printf("\n");
	set_status(2);
}

void	handle_sigquit_pro(int sig)
{
	(void)sig;
	printf("Quit\n");
	set_status(131);
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_global.stop != 2)
		printf("\n");
	set_status(130);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_hevar(int sig)
{
	(void)sig;
	g_global.stop = -42;
	printf("\n");
	close(0);
}

void	begin_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
