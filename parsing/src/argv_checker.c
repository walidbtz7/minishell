/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 21:45:20 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_cargv	*init_cargv(char *src, char **envp)
{
	t_cargv	*cargv;

	if (!src)
		return (NULL);
	cargv = malloc(sizeof(t_cargv));
	cargv->src = src;
	cargv->i = 0;
	cargv->envp = envp;
	cargv->expand = 1;
	cargv->single = 0;
	cargv->dbl = 0;
	cargv->c = src[cargv->i];
	return (cargv);
}

void	cargv_advence(t_cargv *cargv)
{
	if (cargv->c != '\0')
	{
		cargv->i++;
		cargv->c = cargv->src[cargv->i];
	}
}

char	**fargv(t_cargv *check)
{
	char	*new;
	char	*expend;
	char	**test;

	new = ft_strldup("", 0);
	expend = NULL;
	test = NULL;
	while (check->c)
	{
		double_quote(check);
		single_quote(check);
		if (check->c == '$')
		{
			expend = expandenv(check);
			if (expend)
				new = ft_strjoin(new, expend);
			else
				new = NULL;
		}
		else
		{
			new = ft_strjoin(new, charstr(check->c));
			cargv_advence(check);
		}
	}
	if (new)
	{
		test = ft_split(new);
	}
	return (test);
}
