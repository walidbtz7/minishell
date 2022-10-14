/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/14 21:32:57 by mrafik           ###   ########.fr       */
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
	int		t;
	// char	*save;
	t = chdir(path_cd);
	if(t == -1)
	{
		ft_putstr_fd("minishel: cd: ",2);
		ft_putstr_fd(path_cd,2);
		ft_putstr_fd(" No such file or directory\n",2);
		code = 1;
		return(env);
	}
	// if(x == 0)
	// {
		 j = position(env,"OLDPWD");
		// save = env[j];
	//}
	i = position(env,"PWD");
	printf("%s\n",env[i]);
	env[j] = ft_strjoin("OLD",env[i]);
		// chdir(path_cd);
	// if (getcwd(NULL, 0))
		env[i] =  ft_strjoin("PWD=",getcwd(NULL, 0));
	// else
	//  	env[i] = save; 
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
char **remove_var(char **env,int x)
{
	int i;
	int j;
	char **retu;
	
	j = 0;
	i = ft_strlen2(env);
	retu = (char **)malloc(i * sizeof(char *));
	i = 0;
	while (env[i])
	{
		if(i == x)
		{
			if( env[i+1] != '\0')
				i++;
			else
				break;
		}
		retu[j] = env[i];
		j++;
		i++;
	}
	retu[j] = 0;
	return(retu);	
}

char **ft_unset(char **env,char **str)
{
	int i;
	int x,j;
	int	z;

	x = 1;
	i = 0;
	j = 0;
	z = 1;
	while (env[i])
	{
		if(str[z])
		{
			x = 0;
			while((str[z][x] && env[i][x]) && str[z][x] == env[i][x])
				x++;
			if(x != 0 && (!str[z][x]) )
				{
				env = remove_var(env,i);
					z++;
					i = 0;
				// return(env);
				}
			i++;
		}
		else 
			break;
	}
	return(env);
	
}

void	builtins(char **str,t_ex *ex)
{
	int		i;
	char	**tmp;
	
	i = 0;
	if(!ex->env)
	{
		ex->env = (char **)malloc(1 *sizeof(char*));
		ex->env = 0;
	}
	// ex->ex_save = ft_add_old(ex->ex_save);
	if(str)
	{
			if(!ft_strcmp(str[0],"cd"))
			{
				tmp = cd_fuction(str[1],ex->env);
				if(tmp)
				{
					ex->env = tmp;
					ex->ex_save = tmp;
					// ex->ex_save = cd_fuction(str[i],ex->ex_save);
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
			if(!ft_strcmp(str[0],"env"))
			{
				if(!str[1])
				{
					i = 0;
					while(ex->env[i])
						printf("%s\n",ex->env[i++]);
				}
			}
			if(!ft_strcmp(str[0],"unset"))
			{
				ex->env = ft_unset(ex->env,str);
				ex->ex_save = ft_unset(ex->ex_save,str);
			}
			if(!ft_strcmp(str[0],"pwd"))
				printf("%s\n",getcwd(NULL,0));
			if(!ft_strcmp(str[0],"exit"))
				{
					write(2,"exit\n",5);
					exit(0);
				}
	}
}
//exit code 0 succes 1 signal 127 cmd err   258 pars err