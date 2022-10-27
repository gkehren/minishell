/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:29:33 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/27 12:29:33 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
	return (count);
}

static char	**free_all(char **result, int x)
{
	while (x > -1)
		free(result[x--]);
	free(result);
	return (NULL);
}

static char	*split_process(char *s, char c, int *i)
{
	int		j;
	int		count;
	char	*result;

	count = 0;
	j = *i;
	while (s[j] != c && s[j])
	{
		count++;
		j++;
	}
	result = (char *)malloc(sizeof(char) * (count + 1));
	if (result == NULL)
		return (NULL);
	(*i)--;
	j = -1;
	while (s[++(*i)] != c && s[*i])
		result[++j] = s[*i];
	result[j + 1] = '\0';
	return (result);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		i;
	int		x;

	i = 0;
	x = -1;
	result = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (result == NULL)
		return (free_all(result, x));
	while (s[i])
	{
		if (s[i] != c)
		{
			result[++x] = split_process(s, c, &i);
			if (result[x] == NULL)
				return (free_all(result, x));
		}
		else
			i++;
	}
	result[x + 1] = 0;
	return (result);
}
