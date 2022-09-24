/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 20:09:43 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	char	**str;

	new = ft_strldup("", 0);
	expend = NULL;
	str = NULL;
	while (check->c)
	{
		double_quote(check);
		single_quote(check);
		if (check->c == '$')
			new = ft_strjoin(new, expandenv(check));
		else
		{
			new = ft_strjoin(new, charstr(check->c));
			cargv_advence(check);
		}
	}
	if (new)
		str = ft_split(new);
	free(check);
	return (str);
}
