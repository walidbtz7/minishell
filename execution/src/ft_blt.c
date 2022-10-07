/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/07 18:09:13 by mrafik           ###   ########.fr       */
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
				ex->ex_save = export_sort(ex->ex_save);
				while(ex->ex_save[i])
				{
					printf("declare -x %s\n",ex->ex_save[i++]);
				}
	
		}
		if(!ft_strcmp(str[0],"pwd"))
			printf("%s\n",getcwd(NULL,0));
		if(!ft_strcmp(str[0],"exit"))
			exit(0);
	}
	i = 0;
	// while (ex->export[i])
	// 	free(ex->export[i++]);
	// free(ex->export);
	
}
//exit code 0 succes 1 signal 127 cmd err   258 pars err