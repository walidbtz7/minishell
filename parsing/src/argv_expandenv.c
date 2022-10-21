/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expandenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/20 22:23:50 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	envstop(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*checkfirst(t_cargv *cargv)
{
	char	*str;

	str = NULL;
	cargv_advence(cargv);
	if (!ft_isnumber((int) cargv->c))
	{
		if (cargv->c == '?')
		{
			str = ft_itoa(g_code);
			cargv_advence(cargv);
		}
		else if (!envstop(cargv->c))
			str = ft_strldup("$", 1);
	}
	return (str);
}

char	*getenval(char *key, char **envp)
{
	int		i;
	int		j;
	int		exit;
	char	*str;

	i = 0;
	exit = 0;
	str = NULL;
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
		str = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
	free(key);
	return (str);
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
			var = ft_strjoin_free(var, charstr(cargv->c));
			cargv_advence(cargv);
		}
		var = getenval(var, cargv->envp);
		return (var);
	}
	else
		cargv_advence(cargv);
	return (ft_strldup("$", 1));
}
