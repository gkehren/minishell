#include "minishell.h"

int	main(void)
{
	char	*input;

	while (42)
	{
		input = readline("First prompt :");
		generate_token(input);
		//printf("taille str : %d\n", count_charset(" \t", input));
		free(input);
	}
	return (0);
}
