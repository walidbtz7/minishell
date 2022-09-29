/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:43:08 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/29 19:39:25 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*avai_path(char *str,char *cmd)
{
	char	**pos;
	int		i;

	i = 0;
	pos = ft_split(ft_split(str, '=')[1], ':');
	while(pos[i])
	{
		if (open(ft_strjoin(pos[i],cmd),0)  != -1)
		{
			return (ft_strjoin(pos[i],cmd));
		}
		i++;
	}
	return (NULL);
}

char *path(char **env,char *search)
{
	int i;
	int j;
	
	i = 0;
	while(env[i])
	{
		j = 0;
		while(env[i][j])
		{
			if(env[i][j] == search[j] && (env[i][j] != '\0' || search[j] != '\0'))
			{
				j++;
				if(!search[j])
					return (env[i]);
			}
			else
				break;
		}
		i++;
	}
	return(NULL);
}
int check_echo(char **str)
{
	int i;
	
	i = 1;
	while (str[1][i])
	{
		if(str[1][0] != '-')
			return(0);
		if(str[1][i] != 'n')
			return(0);
		i++;
	}
return(1);
}
void	echo_function(char **str)
{
	int i;

	i = 1;
	if(check_echo(str))
		i = 2;
	while (str[i])
	{
		printf("%s %d",str[i],i);
		i++;
	}
	if(!check_echo(str))
		printf("\n");
}
void run_cmd(char **env,char **av)
{
	char *cmd_path;
	char *cmd;

	if(!av)
		return;
	cmd = ft_strjoin_free(ft_strdup("/"), av[0]);
	cmd_path = avai_path(path(env, "PATH"), cmd);
	free(cmd);
	execve(cmd_path,av, env);
}