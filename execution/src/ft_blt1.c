/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:31:41 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 22:23:50 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	position(char **env, char *search)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (env)
	{
		while (env[i])
		{
			j = 0;
			while (env[i][j])
			{
				if (env[i][j] == search[j] && (env[i][j] || search[j]))
				{
					j++;
					if (!search[j])
						return (i);
				}
				else
					break ;
			}
			i++;
		}
	}
	return (-1);
}

void	cd_update(char **env)
{
	int		i;
	int		j;
	char	*pwd;
	char	*tmp;

	j = position(env, "OLDPWD");
	i = position(env, "PWD");
	if (j == -1 || i == -1)
		return ;
	pwd = ft_strdup(env[i]);
	free(env[j]);
	env[j] = ft_strjoin98("OLD", pwd);
	tmp = getcwd(NULL, 0);
	pwd = env[i];
	free(env[i]);
	if (tmp)
		env[i] = ft_strjoin98("PWD=", tmp);
}

char	**cd_fuction(char *path_cd, char **env, int d)
{
	static int	t;

	if (d == 1)
	{
		t = chdir(path_cd);
		if (t == -1)
		{
			ft_putstr_fd("minishel: cd: ", 2);
			ft_putstr_fd(path_cd, 2);
			ft_putstr_fd(" No such file or directory\n", 2);
			g_code = 1;
			return (env);
		}
	}
	if (t >= 0)
	{
		cd_update(env);
		g_code = 0;
	}
	return (env);
}

int	check_echo(char **str)
{
	int	i;
	int	x;
	int	r;

	x = 1;
	r = 0;
	while (str[x])
	{
		i = 0;
		if (i == 0 && str[x][i] == '-')
		{
			i = 1;
			while (str[x][i] && str[x][i] == 'n')
			{
				if (!str[x][i + 1])
						r = x;
				i++;
			}
		}
		else
			break ;
	x++;
	}
	return (r);
}

void	echo_function(char **str)
{
	int	i;
	int	s;

	i = 1;
	if (!str[1])
	{
		printf("\n");
		return ;
	}
	i = check_echo(str);
	s = i;
	if (i == 0)
		i = 1;
	else
		i++;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (s == 0 || !str)
		printf("\n");
}
