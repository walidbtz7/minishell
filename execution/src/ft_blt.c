/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/08 21:26:23 by mrafik           ###   ########.fr       */
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
	// if(x == 0)
	// {
		j = position(env,"OLDPWD");
		save = env[j];
	//}
	i = position(env,"PWD");
	env[j] = ft_strjoin("OLD",env[i]);
	if (getcwd(NULL, 0))
		env[i] =  ft_strjoin("PWD=",getcwd(NULL, 0));
	else
	 	env[i] = save; 
	return(env);
}

int check_echo(char **str)
{
	int i;
	int	x;
	int r;
	
	x = 1;
	r = 0;
	while(str[x])
	{
		i = 0;
			if(i == 0 && str[x][i] == '-')
			{
				i = 1;
				while(str[x][i] && str[x][i] == 'n')
				{
					if(!str[x][i+1])
							r = x;
					i++;
				}
			}
			else
				break;
		x++;
	}
	return(r);
}

void	echo_function(char **str)
{
	int i;
	int s;
	i = 1;
	if(!str[1])
		return;
	i = check_echo(str);
	s = i;
	if(i == 0)
		i = 1;
	else
		i++;
	while (str[i])
	{
		printf("%s",str[i]);
		if(str[i+1])
			printf(" ");
		i++;
	}
	if(s == 0)
		printf("\n");
}

void	builtins(char **str,t_ex *ex)
{
	int		i;
	char	**tmp;
	
	i = 0;
	// ex->ex_save = ft_add_old(ex->ex_save);
	if(str)
	{
		if(!ft_strcmp(str[0],"cd"))
		{
			tmp = cd_fuction(str[1],ex->env);
			if(tmp)
			{
				ex->env = tmp;
				ex->ex_save = cd_fuction(str[i],ex->ex_save);
			}		
		}
		if(!ft_strcmp(str[0],"echo"))
				echo_function(str);
		if(!ft_strcmp(str[0],"export"))
		{
			
				ex->env = export_cmd(ex->env,str,ex);
			if(!str[1])
			{
				ex->export = export_sort(ex->ex_save);
				i = 0;
				while(ex->export[i])
					printf("declare -x %s\n",ex->export[i++]);
			}
		}
		if(!ft_strcmp(str[0],"pwd"))
			printf("%s\n",getcwd(NULL,0));
		if(!ft_strcmp(str[0],"exit"))
			exit(0);
	}
}
//exit code 0 succes 1 signal 127 cmd err   258 pars err