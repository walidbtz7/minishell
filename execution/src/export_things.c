/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/09 11:30:41 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int ft_end(t_ex *ex,char **export)
{
	
	if((ex->len-1) == ex->x)
	{	
		ex->tmp2[ex->i][ex->y++] = export[ex->i][ex->x];
		if(ex->e == 1)
			ex->tmp2[ex->i][ex->y++] = '"';
		ex->tmp2[ex->i][ex->y]='\0';
		return(0);
	}
	return(1);
}

int ft_close(t_ex	*ex,char **export)
{
	if(export[ex->i][ex->x] == '=' )
	{
		ex->tmp2[ex->i][ex->y++] = export[ex->i][ex->x];
		if(export[ex->i][ex->x+1]	!= '\0')
		{
			ex->x++;
			ex->tmp2[ex->i][ex->y++] = '"';
		}
		else
		{
			ex->tmp2[ex->i][ex->y++] = '"';
			ex->tmp2[ex->i][ex->y++] = '"';
			ex->tmp2[ex->i][ex->y]='\0';
			return(0);
		}
		ex->e = 1;
	}
	return(1);
}
void	 ft_free_e(char **str)
{
	int i;
	i = 0;

	while (str[i])
		free(str[i++]);
	free(str);
	
}

char **ft_add(char **export)
{
	t_ex ex;
	
	ex.i = 0;
	ex.tmp2 = (char **)malloc((ft_strlen2(export)+1) * sizeof(char *));
	while (export[ex.i])
	{
		ex.len = ft_strlen((export[ex.i]));
		ex.tmp2[ex.i] = (char *)malloc((ex.len + 4) *sizeof(char));
		ex.y  = 0;
		ex.e = 0;
		ex.x =  0;
		while (export[ex.i][ex.x])
		{
			
			if(!ft_close(&ex,export))
				break;
			if(!ft_end(&ex,export))
					break;
			ex.tmp2[ex.i][ex.y++] = export[ex.i][ex.x++];
		}
		ex.i++;
	}
		ex.tmp2[ex.i] = NULL;
	return(ex.tmp2);
}
int ft_strlen2(char **str)
{
	int i;
	i = 0;
	if(str)
	{
		while (str[i])
		i++;
	}
	return(i);
}
char **ft_dup(char **str)
{
	char **tmp;
	int		i;
	
	i = ft_strlen2(str);
	tmp = (char **)malloc((i +1) * sizeof(char *));
	i = 0; 
	while (str[i])
	{
		tmp[i] = ft_strdup(str[i]);
		i++;
	}
	tmp[i] = NULL;
	return(tmp);
}

char **export_sort(char **envp)
{
	int i;
	int x;
	// char **export;
	char	*tmp;
	
	i = 0;
	if(envp)
	{
		while (envp[i])
		{
			x = 0;
			while (envp[i + x])
			{
				if(ft_strcmp(envp[i],envp[i + x]) > 0)
				{
					tmp = envp[i];
					envp[i] = envp[i+x];
					envp[i+x] = tmp;
					//free(tmp);
				}
				x++;
			}
			i++;
		}
		envp = ft_add(envp);
	}
	return(envp);
}

int	check_cmd_export(char *str)
{
	if(ft_isnumber(str[1]))
	{
		printf("export: `%s': not a valid identifier",str);
		return(0);
	}
	return(1);
}

int ft_search(char *str,char *exp)
{
	int i;
	int x;
	i = 0;
	x = 0;
	// if(!str || !exp)
	// 	return(0);
	while (str[x] && str[x] != '=')
	{
		x++;
	}
	if(!ft_strncmp(exp,str,x) && str[x] == '\0')
		return(2);
	if(!ft_strncmp(exp,str,x))
		return(1);
	return(0);
}

int ft_strcmp2(char **env,char *str)
{
	int i;
	
	i = 0;
	if(env && str)
	{
		while (env[i])
		{
			if(ft_search(str,env[i]))
				return(1);
			i++;
		}
	}
	return(0);
}

void ft_stock_save(t_ex *expo,char **env,char **str,int x)
{
	int i;
	int e;
	
	i =  0;
	i = ft_strlen2(env);
	if(!ft_strcmp2(env,str[x]))
			i = i+1;
	expo->tmp = (char **)malloc((i+1) * sizeof(char *));
	i = 0;
	if(env && str)
	{
		while (env[i])
		{
			e = ft_search(str[x],env[i]);
			if(e)
				{
					expo->tmp[i] = ft_strdup(str[x]);
				}
			else
				expo->tmp[i] = env[i];
			i++;
		}
		if(!e)
		{
			expo->tmp[i] = str[x];
			expo->tmp[i+1] = 0;
		}
		else
			expo->tmp[i]= 0;
	}
	// i = 0;
	// while (expo->tmp[i])
	// {
	// 	printf("%s  \n",expo->tmp[i++]);
	// }
	
}

void ft_stock(t_ex *expo,char **env,char **str,int x)
{
	int i;
	int e;
	
	i =  0;
	i = ft_strlen2(env);
	if(!ft_strcmp2(env,str[x]))
			i = i+1;
	expo->tmp = (char **)malloc((i+1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		e = ft_search(str[x],env[i]);
		if(e == 1)
			expo->tmp[i] = str[x];
		else
			expo->tmp[i] = env[i];
		i++;
	}
	if(e == 0)
	{
		expo->tmp[i] = str[x];
		expo->tmp[i+1] = 0;
	}
	else
	expo->tmp[i] = 0;
}

char	**export_cmd(char **env,char **str,t_ex *ex)
{
	t_ex expo;
	int i;
	int x;
	// int e;

	i = 0;
	i = ft_strlen2(env);
	x = 1;
	expo.tmp = (char **)malloc((i+2) * sizeof(char *));
	expo.tmp = env;
	while (str[x])
	{
		if(check_cmd_export(str[x]))
		{
			if(str[0])
			{
				ft_stock(&expo,env,str,x);
				if(ft_strchr(str[x],'='))
					env = ft_dup(expo.tmp);
				expo.tmp = ex->ex_save;
				ft_stock_save(&expo,ex->ex_save,str,x);
				printf("hna\n");
				ex->ex_save = ft_dup(expo.tmp);
			}
		}
	x++;
	}
	return(env);
}