/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 01:03:56 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print2d(t_ex *ex)
{
	int	i;

	i = 0;
	while (ex->export[i])
		printf("declare -x %s\n", ex->export[i++]);
}

char	**export_helper1(t_ex *expo, char **env, char **str, t_ex *ex)
{
	ft_stock(expo, env, str, expo->x);
	if (ft_strchr(str[expo->x], '='))
	{
		ft_free_e(env);
		env = ft_dup(expo->tmp);
	}
	free(expo->tmp);
	ft_stock_save(expo, ex->ex_save, str, expo->x);
	ft_free_e(ex->ex_save);
	ex->ex_save = ft_dup(expo->tmp2);
	free(expo->tmp2);
	return (env);
}

void	check_ex_print(int x, t_ex *ex)
{
	if (x == 1)
	{
		ex->export = export_sort(ft_dup(ex->ex_save));
		print2d(ex);
		ft_free_e(ex->export);
	}
}

char	**export_helper2(char **str, t_ex *expo, t_ex *ex, char **env)
{
	if (str[0])
	{
		if (str[1][0])
			env = export_helper1(expo, env, str, ex);
		else
			ft_putstr_fd("minishell :export: `': not a valid identifier\n", 2);
	}
	return (env);
}

char	**export_cmd(char **env, char **str, t_ex *ex)
{
	t_ex	expo;
	int		i;
	int		check;

	i = 0;
	i = ft_strlen2(env);
	expo.x = 1;
	expo.tmp = NULL;
	expo.tmp2 = NULL;
	while (str[expo.x])
	{
		check = check_cmd_export(str[expo.x]);
		if (check == 1)
			env = export_helper2(str, &expo, ex, env);
		else if (check == 2)
		{
			check_ex_print(expo.x, ex);
			break ;
		}
		expo.x++;
	}
	return (env);
}
