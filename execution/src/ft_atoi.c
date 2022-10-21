/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:13:56 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 18:43:35 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	long_handle(int x, int i, int j)
{
	if (i >= 19 && j > 0)
		return (-1);
	if (i >= 19 && j < 0)
		return (0);
	else
		return (x);
}

static int	f(char a)
{
	int	i;

	i = 0;
	if (a == ' '
		|| a == '\t'
		|| a == '\n'
		|| a == '\v'
		|| a == '\f'
		|| a == '\r' )
	{
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 1;
	x = 0;
	while (f(str[i]) == 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			j = j * (-1);
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' )
	{
		x = x * 10 + (str[i] - '0');
		i++;
	}
	x = long_handle(x, i, j);
	return (x * j);
}
