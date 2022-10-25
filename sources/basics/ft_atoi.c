/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:08:41 by gkehren           #+#    #+#             */
/*   Updated: 2022/10/25 22:08:59 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

long long	ft_atoll(const char *s)
{
	long long	n;
	int			i;
	int			sign;

	i = 0;
	n = 0;
	sign = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (sign > 0 && (LLONG_MAX - s[i] + '0') / 10 < n)
			return (0);
		if (sign < 0 && (LLONG_MIN + s[i] - '0') / 10 > -n)
			return (0);
		n = 10 * n + (s[i] - '0');
		i++;
	}
	return (sign * n);
}

long long	ft_atoi(char *str)
{
	int			i;
	int			neg;
	long long	result;

	result = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		neg = -neg;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * neg);
}
