
#include "minishell.h"

// size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
// {
// 	size_t	i;

// 	if (dstsize != 0)
// 	{
// 		i = 0;
// 		while (i + 1 < dstsize && src[i])
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (ft_strlen(src));
// }

static int	ft_find_line(char *buff, int buff_size)
{
	int	i;

	i = 0;
	while (buff[i] && i < buff_size)
	{
		if (buff[i] == '\n')
		{
			return (i);
		}	
		i++;
	}
	return (-1);
}

static char	*initialize_buff(int *ret, char *save, int fd)
{
	char	*new_buff;
	int		i;

	i = -1;
	new_buff = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (new_buff == NULL)
		return (NULL);
	if (save[0] != '\0')
	{
		ft_strlcpy(new_buff, save, BUFFER_SIZE + 1);
		while (++i < BUFFER_SIZE + 1)
			save[i] = '\0';
		*ret = 1;
	}
	else
	{
		*ret = read(fd, new_buff, BUFFER_SIZE);
		if (*ret == 0)
		{
			free(new_buff);
			return (NULL);
		}	
	}
	return (new_buff);
}

static char	*process_line(char *result, char *buff, int	*ret, int fd)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	while (*ret && ft_find_line(buff, BUFFER_SIZE) == -1)
	{
		tmp = result;
		result = ft_strjoin(tmp, buff);
		*ret = read(fd, buff, BUFFER_SIZE);
		buff[*ret] = '\0';
		free(tmp);
	}
	if (ret)
	{
		tmp = ft_subuff(buff, ft_find_line(buff, BUFFER_SIZE));
		tmp2 = result;
		result = ft_strjoin(result, tmp);
		free(tmp);
		free(tmp2);
	}
	return (result);
}

char	*get_next_line(int fd)
{
	char			*result;
	static char		save[BUFFER_SIZE + 1];
	char			*buff;
	int				ret;

	if (BUFFER_SIZE < 1 || fd < 0 || (read(fd, 0, 0) <= -1))
		return (NULL);
	result = NULL;
	buff = initialize_buff(&ret, save, fd);
	if (buff == NULL)
		return (NULL);
	result = process_line(result, buff, &ret, fd);
	if (ret)
		ft_substr(buff, ft_find_line(buff, BUFFER_SIZE + 1), save);
	free(buff);
	return (result);
}
