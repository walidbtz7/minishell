/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:01:41 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 01:04:34 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_help_save(char **env, char **str, t_ex *expo, int x)
{
	int	i;
	int	e;

	i = 0;
	while (env[i])
	{
		e = ft_search1(str[x], env[i]);
		if (e == 1)
			expo->tmp2[i] = str[x];
		else if (e >= 0)
			expo->tmp2[i] = env[i];
		i++;
	}
	return (i);
}

void	ft_stock_save(t_ex *expo, char **env, char **str, int x)
{
	int	i;
	int	z;

	z = 0;
	i = 0;
	i = ft_strlen2(env);
	if (!ft_strcmp3(env, str[x]))
	{
		i = i + 1;
		z = 1;
	}
	expo->tmp2 = (char **)malloc((i + 1) * sizeof(char *));
	i = ft_help_save(env, str, expo, x);
	if (z == 1)
	{
		expo->tmp2[i] = str[x];
		expo->tmp2[i + 1] = 0;
	}
	else
		expo->tmp2[i] = 0;
}
