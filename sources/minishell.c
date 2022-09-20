#include "minishell.h"

int	main(void)
{
	char	*input;

	while (42)
	{
		input = readline("First prompt :");
		free(input);
	}
	return (0);
}
