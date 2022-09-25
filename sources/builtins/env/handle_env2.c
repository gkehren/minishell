#include "minishell.h"

char	**malloc_not_init(char *env_part)
{
	char	**result;
	int		i;

	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL)
		return (NULL);
	result[0] = (char *)malloc(sizeof(char) * (ft_strlen(env_part) + 1));
	if (result[0] == NULL)
		return (NULL);
	i = 0;
	while (env_part[i])
	{
		result[0][i] = env_part[i];
		i++;
	}
	result[0][i] = '\0';
	result[1] = NULL;
	return (result);
}

int	malloc_failed_env(t_list **venv)
{
	ft_lstclear(venv, &del_venv);
	printf("ENV creation failed !\n");
	return (1);
}