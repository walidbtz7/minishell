/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:44:27 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 22:02:42 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exist(char **env, char *args)
{
	char	**str;
	char	**tmp;
	int		i;

	i = 0;
	if (!env || !env[0])
		return (-3);
	str = ft_split(args, '=');
	while (env[i])
	{	
		tmp = ft_split(env[i], '=');
		if (!ft_strcmp(str[0], tmp[0]))
		{
			ft_free_e(str);
			ft_free_e(tmp);
			return (i);
		}
		ft_free_e(tmp);
		i++;
	}
	ft_free_e(str);
	return (-1);
}

void	add_neew(char ***env, char *args)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *env;
	(*env) = (char **)(malloc((ft_strlen2(*env) + 2) * sizeof(char *)));
	i = 0;
	while ((tmp)[i])
	{
		(*env)[i] = tmp[i];
		i++;
	}
	free(tmp);
	(*env)[i] = ft_strdup(args);
	(*env)[i + 1] = 0;
}

void	add_var(char ***env, char *args, int i)
{
	if (my_ft_strchr(args, '='))
	{
		if (i > 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(args);
		}
		else
			add_neew(env, args);
	}
	else
	{
		if (i > 0)
		{
			if (my_ft_strchr(args, '='))
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(args);
			}
			else
				return ;
		}
		else
			add_neew(env, args);
	}
}

void	ft_stock(char ***env, char *args)
{		
	int	i;

	i = exist((*env), args);
	if (i == -3)
	{
		if ((*env))
			free(*env);
		(*env) = (char **)malloc(sizeof (char *));
		(*env)[0] = NULL;
	}
	if (args[0])
		add_var(env, args, i);
	else
		ft_putstr_fd("minishell :export: `': not a valid identifier\n", 2);
}

void	ft_export(char ***env, char ***export, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (check_cmd_export(args[i]))
		{
			if (my_ft_strchr(args[i], '='))
				ft_stock(env, args[i]);
			ft_stock(export, args[i]);
			code = 0;
		}
		i++;
	}
}
