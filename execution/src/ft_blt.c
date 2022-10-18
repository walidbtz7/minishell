/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/18 09:46:17 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int position(char **env,char *search)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	if(env)
	{
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
	}
	return(-1);
}

char **cd_fuction(char *path_cd,char **env)
{
	int		i;
	int		j;
	int		t;
	char *tmp;
	char *pwd;
	
	t = chdir(path_cd);
	if(t == -1)
	{
		ft_putstr_fd("minishel: cd: ",2);
		ft_putstr_fd(path_cd,2);
		ft_putstr_fd(" No such file or directory\n",2);
		code = 1;
		return(env);
	}
	
	j = position(env,"OLDPWD");
	i = position(env,"PWD");
	if(j == -1 || i == -1)
		return(env);
	printf("%d %s\n", i , env[i]);
	pwd = ft_strdup(env[i]);
	free(env[j]);
	env[j] = ft_strjoin98("OLD",pwd);
	tmp = getcwd(NULL, 0);
	pwd = env[i];
	free(env[i]);
	if(tmp)
		env[i] =  ft_strjoin98("PWD=",tmp);
	// free(tmp);
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
	if(s == 0 || !str)
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
	if(i == 1)
		return(NULL);
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
	ft_free_e(env);
	retu[j] = 0;
	return(retu);	
}

char **ft_unset(char **env,char **str)
{
	int i;
	int x,j;
	int	z;

	i = ft_strlen2(env);
	if(i == 1)
		return(NULL);
	x = 1;
	i = 0;
	j = 0;
	z = 1;
	if(env)
	{
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
	}
	return(env);
	
}

void	builtins(char **str,t_ex *ex,int in)
{
	int		i;
	char	**tmp;
	char    **yo;
	char	*pwd;
	
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
				tmp = ft_dup(cd_fuction(str[1],ex->env));
				if(tmp)
				{
					ft_free_e(ex->env);
					ft_free_e(ex->ex_save);
					ex->env = ft_dup(tmp);
					ex->ex_save = ft_dup(tmp);
					ft_free_e(tmp);
					// ex->ex_save = cd_fuction(str[i],ex->ex_save);
				}
				ft_free_e(str);
			}
			else if(!ft_strcmp(str[0],"echo"))
				{
					echo_function(str);
					ft_free_e(str);
					
				}
			else if(!ft_strcmp(str[0],"export"))
			{
				if(str[1])
				{
					yo = ft_dup(ex->env);
					ft_free_e(ex->env);
					printf("%p\n",ex->env);
					ex->env = ft_dup(export_cmd(yo,str,ex));
					 ft_free_e(yo);
				}
					
				if(!str[1])
				{
					if(ex->ex_save)
					{
						ex->export = export_sort(ft_dup(ex->ex_save));
						i = 0;
						while(ex->export[i])
							printf("declare -x %s\n",ex->export[i++]);
						ft_free_e(ex->export);
					}
				}
				ft_free_e(str);
			}
			else if(!ft_strcmp(str[0],"env"))
			{
				if(!str[1])
				{
					i = 0;
					while(ex->env[i])
						printf("%s\n",ex->env[i++]);
				}
				ft_free_e(str);
			}
			else if(!ft_strcmp(str[0],"unset"))
			{
				ex->env = ft_unset(ex->env,str);
				ex->ex_save = ft_unset(ex->ex_save,str);
				ft_free_e(str);
			}
			else if(!ft_strcmp(str[0],"pwd"))
				{
					pwd = getcwd(NULL,0);
					printf("%s\n",pwd);
					free(pwd);
					ft_free_e(str);
				}
			else if(!ft_strcmp(str[0],"exit"))
				{
					if(in == 0)
					{
						if(ft_strlen2(str) == 1)
						{
							write(2,"exit\n",5);
							exit(0);
						}
					}
					if(ft_strlen2(str) > 2)
					{
						ft_putstr_fd("minishell: exit: too many arguments\n",2);
						exit(1);
					}
					else if(str[1] && str[1][0])
					{
						if(!ft_isnumber(str[1][0]))
						{
							ft_putstr_fd("minishell: exit: ",2);
							ft_putstr_fd(str[1],2);
							ft_putstr_fd("numeric argument required\n",2);
							exit(0);
						}
						exit(atoi(str[1]));
					}
					ft_free_e(str);
				}
	}
}
//exit code 0 succes 1 signal 127 cmd err   258 pars err