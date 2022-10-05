/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/05 19:00:23 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int position(char **env,char *search)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(env[i])
	{
		j = 0;
		while(env[i][j])
		{
			if(env[i][j] == search[j] && (env[i][j] != '\0' || search[j] != '\0'))
			{
				j++;
				if(!search[j])
					return(i);
			}
			else
				break;
		}
		i++;
	}
	return(0);
}

char **cd_fuction(char *path_cd,char **env)
{
	int		i;
	int		j;
	char	*save;
	
	if(chdir(path_cd))
	{
		printf("faild to %s\n",path_cd);
		return(0);
	}
	i = position(env,"PWD");
	j = position(env,"OLDPWD");
	save = env[j];
	env[j] = env[i];
	if (getcwd(NULL, 0))
		env[i] =  getcwd(NULL, 0);
	else
		env[i] = save; 
	return(env);
}
int check_echo(char **str)
{
	int i;
	
	i = 1;
	while (str[1][i])
	{
		if(str[1][0] != '-')
			return(0);
		else if(str[1][i] != 'n')
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
		printf("%s",str[i]);
		if(str[i+1])
			printf(" ");
		i++;
	}
	if(!check_echo(str))
		printf("\n");
}

void	builtins(char **str,t_ex *ex)
{
	int		i;
	char	**tmp;
	
	i = 0;
	if(str)
	{
		if(!ft_strcmp(str[0],"cd"))
		{
			tmp = cd_fuction(str[1],ex->env);
			if(tmp)
				{
					ex->env = ft_dup(tmp);
					ex->export = export_sort(ex->env);
					while (ex->env[i])
					{
						printf("%s\n",ex->env[i++]);
					}
					
				}
		}
		if(!ft_strcmp(str[0],"echo"))
				echo_function(str);
		if(!ft_strcmp(str[0],"export"))
		{
				ex->env = export_cmd(ex->env,str,ex);
				i = 0;
				// while(ex->export[i])
				// {
				// 	printf("%s\n",ex->export[i++]);
				// }
	
		}
		if(!ft_strcmp(str[0],"pwd"))
			printf("%s\n",getcwd(NULL,0));
	}
	i = 0;
	// while (ex->export[i])
	// 	free(ex->export[i++]);
	// free(ex->export);
	
}