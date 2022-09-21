/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expandenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 21:43:58 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	envstop(char c)
{
	if (isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*checkfirst(t_cargv *cargv)
{
	cargv_advence(cargv);
	if (!isnumber((int) cargv->c))
	{
		if (cargv->c == '?')
			return ("0");
		else if (!envstop(cargv->c))
			return ("$");
	}
	return (NULL);
}

char	*getenval(char *key, char **envp)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	exit = 0;
	if (!key)
		return (0);
	while (envp[i] && !exit)
	{
		j = 0;
		while (key[j] == envp[i][j] && key && envp[i][j])
			j++;
		if (j == ft_strlen(key))
			exit = 1;
		else
			i++;
	}
	if (j == ft_strlen(key) && envp[i][j] == '=')
		return (ft_substr(envp[i], j + 1, ft_strlen(envp[i])));
	return (NULL);
}

char	*expandenv(t_cargv *cargv)
{
	char	*var;

	var = NULL;
	if (cargv->expand == 1)
	{
		var = checkfirst(cargv);
		if (var)
			return (var);
		while (envstop(cargv->c))
		{
			var = ft_strjoin(var, charstr(cargv->c));
			cargv_advence(cargv);
		}
		var = getenval(var, cargv->envp);
		return (var);
	}
	else
		cargv_advence(cargv);
	return ("$");
}
