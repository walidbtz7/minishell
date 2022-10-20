/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_thing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:58:41 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 18:34:18 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		i++;
	}
	return (i);
}

char	**ft_dup(char **str)
{
	char	**tmp;
	int		i;

	i = ft_strlen2(str);
	tmp = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (str[i])
	{
		tmp[i] = ft_strdup(str[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	sort_help(char **envp, int i)
{
	int		x;
	char	*tmp;

	x = 0;
	while (envp[i + x])
	{
		if (ft_strcmp(envp[i], envp[i + x]) > 0)
		{
			tmp = envp[i];
			envp[i] = envp[i + x];
			envp[i + x] = tmp;
		}
		x++;
	}
}

char	**export_sort(char **exp)
{
	int		i;
	char	**envp;

	i = 0;
	if (exp && exp[0])
	{
		envp = ft_dup(exp);
		if (envp)
		{
			while (envp[i])
			{
				sort_help(envp, i);
				i++;
			}
			envp = ft_add(envp);
		}
		return (envp);
	}
	return (NULL);
}

int	ft_notvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#' && i == 0)
			return (2);
		if (str[i] == '!' || str[i] == '"'
			|| (str[i] >= '$' && str[i] < '0')
			|| (str[i] >= '[' && str[i] <= '`')
			|| (str[i] >= '{' && str[i] <= '~'))
			return (1);
		if ((str[i] >= '0' && str[i] <= '9') && i == 0)
			return (1);
		i++;
	}
	return (0);
}
