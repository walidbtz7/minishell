/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/04 23:56:20 by mrafik           ###   ########.fr       */
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
	 
	while (str[i])
		i++;
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
	char **export;
	char	*tmp;
	char	**tmp2;
	
	i = 0;
	export = ft_dup(envp);
	while (export[i])
	{
		x = 0;
		while (export[i +x])
		{
			if(ft_strcmp(export[i],export[i + x]) > 0)
			{
				tmp = export[i];
				export[i] = export[i+x];
				export[i+x] = tmp;
				//free(tmp);
			}
			x++;
		}
		i++;
	}
	tmp2 = ft_add(export);
	i =0;
	while (export[i])
		free(export[i++]);
	free(export);
	
	return(tmp2);
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
	i =0;
	while (env[i])
	{
		if(ft_search(str,env[i]))
			return(1);
		i++;
	}
	return(0);
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
void	export_cmd(char **str,t_ex *ex)
{
	t_ex expo;
	int i;
	int x;
	
	i = ft_strlen2(ex->env);
	x = 1;
	expo.tmp = ex->env;
	while (str[x])
	{
		if(check_cmd_export(str[x]))
		{
			if(str[0])
				ft_stock(&expo,ex->env,str,x);
				
		}
		if(ft_strchr(str[x],'='))
		{
			ex->env = expo.tmp;
		}
		x++;
	}
}