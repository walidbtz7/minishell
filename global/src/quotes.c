/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:30:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 20:39:45 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fsingle(char c, int *single, int dbl)
{
	if (dbl == 0)
	{
		if (c == 39 && *single == 0)
			*single = 1;
		else if (c == 39 && *single == 1)
			*single = 0;
	}
}

void	fdbl(char c, int single, int *dbl)
{
	if (single == 0)
	{
		if (c == 34 && *dbl == 0)
			*dbl = 1;
		else if (c == 34 && *dbl == 1)
			*dbl = 0;
	}
}
