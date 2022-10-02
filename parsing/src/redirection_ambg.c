/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ambg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/02 02:58:49 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	freestrings(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ambiguous_red(char	*str)
{
	char	**check;
	char	*tmp;
	int		res;

	res = 1;
	check = NULL;
	if (str[0])
	{
		tmp = ft_strldup(str, ft_strlen(str));
		check = ft_split_space(tmp);
		if (check[1] != NULL)
			res = 0;
	}
	else
		res = 0;
	if (!res)
	{
		write(2, "minishell : ambiguous redirect\n", 32);
		free(str);
	}
	freestrings(check);
	return (res);
}
