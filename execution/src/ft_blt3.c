/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:33:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 01:39:41 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(char **str, int in)
{
	if (in == 0)
	{
		if (ft_strlen2(str) == 1)
		{
			write(2, "exit\n", 5);
			exit(0);
		}
	}
	if (ft_strlen2(str) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(1);
	}
	else if (str[1] && str[1][0])
	{
		if (!ft_isnumber(str[1][0]))
			exit_err(str);
		exit(atoi(str[1]));
	}
	ft_free_e(str);
}
