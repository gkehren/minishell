#include "minishell.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}