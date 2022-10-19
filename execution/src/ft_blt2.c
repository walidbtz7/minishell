/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:32:30 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 01:39:30 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remov_var_helper(char **env, char **retu, int x, int j)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (i == x)
		{
			if (env[i + 1] != '\0')
				i++;
			else
				break ;
		}
		retu[j] = env[i];
		j++;
		i++;
	}
	free(env);
	retu[j] = 0;
}

char	**remove_var(char **env, int x)
{
	int		i;
	int		j;
	char	**retu;

	j = 0;
	i = ft_strlen2(env);
	retu = (char **)malloc(i * sizeof(char *));
	if (i == 1)
		return (NULL);
	remov_var_helper(env, retu, x, j);
	return (retu);
}

char	**unset_helper(char **str, int z, char **env)
{
	int	x;
	int	i;

	i = 0;
	while (env[i])
	{
		if (str[z])
		{
			x = 0;
			while ((str[z][x] && env[i][x]) && str[z][x] == env[i][x])
				x++;
			if (x != 0 && (!str[z][x]))
			{
				free(env[i]);
				env = remove_var(env, i);
				z++;
				i = 0;
			}
			i++;
		}
		else
			break ;
	}
	return (env);
}

char	**ft_unset(char **env, char **str)
{
	int	i;
	int	z;

	i = ft_strlen2(env);
	if (i == 1)
		return (NULL);
	z = 1;
	if (env)
		env = unset_helper(str, z, env);
	return (env);
}

void	exit_err(char **str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd("numeric argument required\n", 2);
	exit(0);
}
