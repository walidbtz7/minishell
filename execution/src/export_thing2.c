/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_thing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:55:43 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 00:56:36 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_end(t_ex *ex, char **export)
{
	if ((ex->len - 1) == ex->x)
	{	
		ex->tmp2[ex->i][ex->y++] = export[ex->i][ex->x];
		if (ex->e == 1)
			ex->tmp2[ex->i][ex->y++] = '"';
		ex->tmp2[ex->i][ex->y] = '\0';
		return (0);
	}
	return (1);
}

int	ft_close(t_ex *ex, char **export)
{
	if (export[ex->i][ex->x] == '=' )
	{
		ex->tmp2[ex->i][ex->y++] = export[ex->i][ex->x];
		if (export[ex->i][ex->x + 1] != '\0')
		{
			ex->x++;
			ex->tmp2[ex->i][ex->y++] = '"';
		}
		else
		{
			ex->tmp2[ex->i][ex->y++] = '"';
			ex->tmp2[ex->i][ex->y++] = '"';
			ex->tmp2[ex->i][ex->y] = '\0';
			return (0);
		}
		ex->e = 1;
	}
	return (1);
}

void	ft_free_e(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

char	*ft_help_add(t_ex *ex, char **export)
{
	ex->y = 0;
	ex->e = 0;
	ex->x = 0;
	while (export[ex->i][ex->x])
	{
		if (!ft_close(ex, export))
			break ;
		if (!ft_end(ex, export))
			break ;
		ex->tmp2[ex->i][ex->y++] = export[ex->i][ex->x++];
	}
	return (ex->tmp2[ex->i]);
}

char	**ft_add(char	**export)
{
	t_ex	ex;

	ex.tmp2 = NULL;
	ex.i = 0;
	ft_free_e(ex.tmp2);
	ex.tmp2 = (char **)malloc((ft_strlen2(export)+1) * sizeof(char *));
	while (export[ex.i])
	{
		ex.len = ft_strlen((export[ex.i]));
		ex.tmp2[ex.i] = (char *)malloc((ex.len + 4) * sizeof(char));
		ex.tmp2[ex.i] = ft_help_add(&ex, export);
		ex.i++;
	}
	ex.tmp2[ex.i] = 0;
	ft_free_e(export);
	return (ex.tmp2);
}
