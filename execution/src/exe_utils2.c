/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:26:29 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/19 01:10:13 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*avai_path(char *str, char *cmd)
{
	char	**pos;
	int		i;

	i = 0;
	if (str)
	{
		pos = ft_split(ft_split(str, '=')[1], ':');
		while (pos[i])
		{
			if (open(ft_strjoin(pos[i], cmd), 0) != -1)
			{
				return (ft_strjoin(pos[i], cmd));
			}
			i++;
		}
	}
	return (NULL);
}

char	*path(char **env, char *search)
{
	int	i;
	int	j;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			j = 0;
			while (env[i][j])
			{
				if (env[i][j] == search[j]
					&& (env[i][j] != '\0' || search[j] != '\0'))
				{
					j++;
					if (!search[j])
						return (env[i]);
				}
				else
					break ;
			}
			i++;
		}
	}
	return (NULL);
}

void	run_cmd(char **env, char **av)
{
	char	*cmd_path;
	char	*cmd;
	char	*tmp;

	cmd_path = NULL;
	cmd = NULL;
	if (!av)
		return ;
	tmp = ft_strchr(av[0], '/');
	if (tmp)
		cmd_path = av[0];
	else
	{
		cmd = ft_strjoin("/", av[0]);
		cmd_path = avai_path(path(env, "PATH"), cmd);
		free(cmd);
	}
	execve(cmd_path, av, env);
}
