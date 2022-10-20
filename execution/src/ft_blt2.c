/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:32:30 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 22:21:01 by mrafik           ###   ########.fr       */
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
	code = 0;
	return (retu);
}

void	helllp(char ***env, int *i, int *z)
{
	free((*env)[*i]);
	(*env) = remove_var((*env), *i);
	(*z)++;
	*i = 0;
}

char	**unset_helper(char **str, int z, char **env, int d)
{
	int	x;
	int	i;

	i = 0;
	while (env[i])
	{
		if (str[z])
		{
			x = 0;
			if (d == 0 && !check_cmd_export(str[z]))
				break ;
			while ((str[z][x] && env[i][x]) && str[z][x] == env[i][x])
				x++;
			if (x != 0 && (!str[z][x]))
				helllp(&env, &i, &z);
			i++;
		}
		else
			break ;
	}
	return (env);
}

char	**ft_unset(char **env, char **str, int d)
{
	int	i;
	int	z;

	i = ft_strlen2(env);
	if (i == 1)
		return (NULL);
	z = 1;
	if (env)
		env = unset_helper(str, z, env, d);
	return (env);
}
