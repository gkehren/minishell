/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:29:23 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:29:23 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!(*s2) && !(*s1))
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	if (s1[i] > s2[i])
		return (1);
	else if (s1[i] < s2[i])
		return (-1);
	else
		return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i *= -1;
	}
	if (i > 9)
		ft_putnbr_fd(i / 10, fd);
	ft_putchar_fd('0' + (i % 10), fd);
}
