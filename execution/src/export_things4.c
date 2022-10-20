/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:59:52 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 22:00:58 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_cmd_export(char *str)
{
	int	check;

	check = ft_notvalid(str);
	if (check == 1)
	{
		printf("export: `%s': not a valid identifier\n", str);
		code = 1;
		return (0);
	}
	else if (check == 2)
		return (2);
	return (1);
}

int	ft_search1(char *str, char *exp)
{
	int		i;
	int		x;
	char	**rd;

	i = 0;
	x = 0;
	if (str)
	{
		rd = ft_split(str, '=');
		while (exp[x] && exp[x] != '=')
			x++;
		if (!ft_strncmp(exp, rd[0], x) && !rd[0][x] && !rd[1])
		{
			ft_free_e(rd);
			return (3);
		}
		if (!ft_strncmp(exp, rd[0], x) && (!str[x] || str[x] == '='))
		{
			ft_free_e(rd);
			return (1);
		}
		ft_free_e(rd);
		return (0);
	}
	return (-1);
}

int	ft_strcmp3(char **env, char *str)
{
	int	i;

	i = 0;
	if (env && str)
	{
		while (env[i])
		{
			if (ft_search1(str, env[i]) > 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_help_env(char **env, char **str, t_ex *expo, int x)
{
	int	i;
	int	e;

	i = 0;
	while (env[i])
	{
		e = ft_search1(str[x], env[i]);
		if (e == 1)
			expo->tmp[i] = str[x];
		else if (e >= 0)
			expo->tmp[i] = env[i];
		i++;
	}
	return (i);
}

// void	ft_stock(t_ex *expo, char ***env, char **str, int x)
// {
// 	int	i;
// 	int	z;

// 	z = 0;
// 	i = 0;
// 	i = ft_strlen2(*env);
// 	if (!ft_strcmp3(*env, str[x]))
// 	{
// 		i = i + 1;
// 		z = 1;
// 	}
// 	expo->tmp = (char **)malloc((i + 1) * sizeof(char *));
// 	i = ft_help_env(*env, str, expo, x);
// 	if (z == 1)
// 	{
// 		expo->tmp[i] = str[x];
// 		expo->tmp[i + 1] = 0;
// 	}
// 	else
// 		expo->tmp[i] = 0;
// 	free(*env);
// 	*env = expo->tmp;
// }
