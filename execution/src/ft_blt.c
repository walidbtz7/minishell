/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 01:34:17 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_helper(t_ex *ex, char **str, char **tmp)
{
	ft_free_e(ex->env);
	ex->env = ft_dup(tmp);
	ft_free_e(tmp);
	tmp = ft_dup(cd_fuction(str[1], ex->ex_save, 0));
	ft_free_e(ex->ex_save);
	ex->ex_save = ft_dup(tmp);
	ft_free_e(tmp);
}

void	cd_and_echo(t_ex *ex, char **str)
{
	char	**tmp;

	if (!ft_strcmp(str[0], "cd"))
	{
		tmp = ft_dup(cd_fuction(str[1], ex->env, 1));
		if (tmp)
			cd_helper(ex, str, tmp);
		ft_free_e(str);
	}
	else if (!ft_strcmp(str[0], "echo"))
	{
		echo_function(str);
		ft_free_e(str);
	}
}

void	export_and_env(t_ex *ex, char **str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str[0], "export"))
	{
		if (str[1])
			ex->env = export_cmd(ex->env, str, ex);
		if (!str[1])
		{
			ex->export = export_sort(ft_dup(ex->ex_save));
			print2d(ex);
			ft_free_e(ex->export);
		}
		ft_free_e(str);
	}
	else if (!ft_strcmp(str[0], "env"))
	{
		if (!str[1])
		{
			i = 0;
			while (ex->env[i])
				printf("%s\n", ex->env[i++]);
		}
		ft_free_e(str);
	}
}

void	unset_and_pwd(t_ex *ex, char **str)
{
	char	*pwd;

	if (!ft_strcmp(str[0], "unset"))
	{
		ex->env = ft_unset(ex->env, str);
		ex->ex_save = ft_unset(ex->ex_save, str);
		ft_free_e(str);
	}
	else if (!ft_strcmp(str[0], "pwd"))
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
		ft_free_e(str);
	}
}

void	builtins(char **str, t_ex *ex, int in)
{
	if (!ex->env)
	{
		ex->env = (char **) malloc(1 * sizeof(char *));
		ex->env = 0;
	}
	if (str)
	{
		cd_and_echo(ex, str);
		export_and_env(ex, str);
		unset_and_pwd(ex, str);
		if (!ft_strcmp(str[0], "exit"))
			ft_exit(str, in);
	}
}
