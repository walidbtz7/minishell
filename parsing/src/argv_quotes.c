/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/23 18:27:56 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	single_quote(t_cargv *cargv)
{
	if (cargv->dbl == 0)
	{
		if (cargv->c == 39 && cargv->single == 0)
		{
			cargv->single = 1;
			cargv->expand = 0;
		}
		else if (cargv->c == 39 && cargv->single == 1)
		{
			cargv->single = 0;
			cargv->expand = 1;
		}
	}
}

void	double_quote(t_cargv *cargv)
{
	if (cargv->single == 0)
	{
		if (cargv->c == 34 && cargv->dbl == 0)
			cargv->dbl = 1;
		else if (cargv->c == 34 && cargv->dbl == 1)
			cargv->dbl = 0;
	}
}

char	*rmquote(t_cargv *check)
{
	char	*new;
	char	*expend;

	new = ft_strldup("", 0);
	expend = NULL;
	while (check->c)
	{
		double_quote(check);
		single_quote(check);
		if (check->c != 34 && check->c != 39)
			new = ft_strjoin(new, charstr(check->c));
		else if (check->c == 34 && check->single == 1)
			new = ft_strjoin(new, charstr(check->c));
		else if (check->c == 39 && check->dbl == 1)
			new = ft_strjoin(new, charstr(check->c));
		cargv_advence(check);
	}
	free(check);
	return (new);
}
