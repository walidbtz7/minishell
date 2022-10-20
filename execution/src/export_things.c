/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 22:23:50 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print2d(t_ex *ex)
{
	int	i;

	i = 0;
	if (ex->export && ex->export[0])
	{
		while (ex->export[i])
			printf("declare -x %s\n", ex->export[i++]);
	}
	g_code = 0;
}

// void export_helper1(t_ex *expo, char **str, t_ex *ex)
// {
// 	// if (ft_strchr(str[expo->x], '='))
// 	// 	ft_stock(expo, &ex->env, str, expo->x);
// 	// ft_stock_save(expo, &ex->ex_save, str, expo->x);
// 	//system("leaks minishell");
// }

void	check_ex_print(int x, t_ex *ex)
{
	if (x == 1)
	{
		if (ex->ex_save[0])
		{
			ex->export = export_sort(ex->ex_save);
			print2d(ex);
			ft_free_e(ex->export);
		}
	}
}

// void export_helper2(char **str, t_ex *expo, t_ex *ex)
// {
// 	if (str[0])
// 	{
// 		if (str[1][0])
// 			export_helper1(expo, str, ex);
// 		else
// 			ft_putstr_fd("minishell :export: `': not a valid identifier\n", 2);
// 	}
// }

// void export_cmd(char **str, t_ex *ex)
// {
// 	t_ex	expo;
// 	int		i;
// 	int		check;

// 	i = 0;
// 	i = ft_strlen2(ex->env);
// 	expo.x = 1;
// 	expo.tmp = NULL;
// 	expo.tmp2 = NULL;
// 	while (str[expo.x])
// 	{
// 		check = check_cmd_export(str[expo.x]);
// 		if (check == 1)
// 			export_helper2(str, &expo, ex);
// 		else if (check == 2)
// 		{
// 			check_ex_print(expo.x, ex);
// 			break ;
// 		}
// 		expo.x++;
// 	}
// }
