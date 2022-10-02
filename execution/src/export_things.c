/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/02 22:23:22 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <minishell.h>

char **export_sort(char **envp)
{
	int i;
	int x,y;
	char **export;
	char *tmp;
	
	i = 0;
	while(envp[i])
		i++;
	export = (char **)(malloc((i+1) * sizeof(char *)));
	i = 0;
	while (envp[i])
	{
		export[i] = ft_strdup(envp[i]);
		i++;
	}
	export[i] = NULL;
	i = 0;
	while (export[i])
	{
		x = 0;
		while (export[i +x])
		{
			if(ft_strcmp(export[i],export[i+x]) > 0)
			{
				tmp = ft_strdup(export[i]);
				export[i] = ft_strdup(export[i+x]);
				export[i+x] = ft_strdup(tmp);
				free(tmp);
			}
			x++;
		}
		i++;
	}
	i = 0;
	x =  0;
	y  = 0;
	while (export[i])
	{
		tmp = (char *)malloc(ft_strlen((export[i]) + 3) *sizeof(char));
		while (export[i][x])
		{
			if(export[i][x] == '=')
			{
				tmp[y] = export[i][x];
				y++;
				tmp[y] = '"';
			}
			if(!export[i][x+1])
			{	
				tmp[y] = export[i][x];
				y++;
				tmp[y] = '"';
			}
			tmp[y] = export[i][x];
			x++;
			y++;
		}
		tmp[y] = '\0';		
	}
	
	return(export);
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

int ft_strlen2(char **str)
{
	int i;
	i = 0;
	 
	while (str[i])
		i++;
	return(i);
}
char	**export_cmd(char **env,char **str)
{
	char **export= NULL;
	char **tmp;
	int i;
	int x;
	
	i = 0;
	i = ft_strlen2(env);
	export = export_sort(env);
	x = 1;
	tmp = (char **)malloc((i+2) * sizeof(char *));
	tmp = ft_dup(env);
	while (str[x])
	{
		if(check_cmd_export(str[x]))
		{
			if(str[0])
			{
				free(tmp);
				i = ft_strlen2(env);
				tmp = (char **)malloc((i+2) * sizeof(char *));
				i = 0;
				while (env[i])
				{
					tmp[i] = ft_strdup(env[i]);
					i++;
				}
				tmp[i] = ft_strdup(str[x]);
				tmp[i+1] = 0;
			}
		}
	if(ft_strchr(str[x],'='))
		env = ft_dup(tmp);
	x++;
	export = export_sort(tmp);
	}
	
		i = 0;
		while (env[i])
		{
			printf("%s\n",env[i]);
			i++;
		}
	return(env);
}