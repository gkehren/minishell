#include "minishell.h"

char	*ft_strdup(char *s)
{
	int		size;
	char	*copy;

	size = ft_strlen(s) + 1;
	copy = (char *)malloc(sizeof(char) * size);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s, size);
	return (copy);
}
