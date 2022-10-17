/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/17 15:32:49 by mrafik           ###   ########.fr       */
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
int ft_notvalid(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '#' && i == 0)
			return(2);
		if(	str[i] == '!' ||  str[i] == '"' || ( str[i] >= '$' && str[i] < '0') || (str[i] >= '[' && str[i] <= '`') || (str[i] >= '{'&& str[i] <= '~'))
			return(1);
		if((str[i] >= '0' && str[i] <= '9') && i == 0 )
			return(1);
	}
	return(0);
}
int	check_cmd_export(char *str)
{
	int check;
	
	check = ft_notvalid(str);
	if(check == 1)
	{
		printf("export: `%s': not a valid identifier\n",str);
		return(0);
	}
	else if(check == 2)
		return(2);
	return(1);
}



int ft_search1(char *str,char *exp)
{
	int i;
	int x;
	char **rd;

	i = 0;
	x = 0;
	if(str)
	{
		rd = ft_split(str,'=');
		while(exp[x] && exp[x] != '=')
			x++;
		if(!ft_strncmp(exp,rd[0],x) && !rd[0][x] && !rd[1])
			return(3);
		if(!ft_strncmp(exp,rd[0],x) && (!str[x] || str[x] == '='))
			return(1);
		return(0);
	}
	return(-1);
}

int ft_strcmp3(char **env,char *str)
{
	int i;
	
	i = 0;
	if(env && str)
	{
		while (env[i])
		{
			if(ft_search1(str,env[i]) > 0)
				return(1);
			i++;
		}
	}
	return(0);
}


void ft_stock(t_ex *expo,char **env,char **str,int x)
{
	int i;
	int e;
	int z;
	
	z= 0;
	i =  0;
	i = ft_strlen2(env);
	if(!ft_strcmp3(env,str[x]))
	{
		i = i+1;
		z = 1;
	}
	expo->tmp = (char **)malloc((i+1) * sizeof(char *));
	i = 0;
	if(env)
	{
		while (env[i])
		{
			e = ft_search1(str[x],env[i]);
			if(e == 1)
				expo->tmp[i] = str[x];
			else if(e >= 0)
				expo->tmp[i] = env[i];
			i++;
		}
	}
	if(z  == 1)
	{
		expo->tmp[i] = str[x];
		expo->tmp[i+1] = 0;
	}
	else
	expo->tmp[i] = 0;
}
void print2d(t_ex *ex)
{
	int i;
	i = 0;
	while (ex->export[i])
		printf("declare -x %s\n",ex->export[i++]);
}
char	**export_cmd(char **env,char **str,t_ex *ex)
{
	t_ex expo;
	int i;
	int x;
	int check;

	i = 0;
	i = ft_strlen2(env);
	x = 1;
	while (str[x])
	{
		check = check_cmd_export(str[x]);
		if(check == 1)
		{
			if(str[0])
			{
				if(str[1][0])
				{
					ft_stock(&expo,env,str,x);
					if(ft_strchr(str[x],'='))
						env = ft_dup(expo.tmp);
					expo.tmp = ex->ex_save;
					ft_stock(&expo,ex->ex_save,str,x);
					ex->ex_save = ft_dup(expo.tmp);
				}
				else
					ft_putstr_fd("minishell :export: `': not a valid identifier\n",2);
			}
		}
		else if(check == 2)
		{
			ex->export = export_sort(ex->ex_save);
			print2d(ex);
			break;
		}
		x++;
	}
	return(env);
}