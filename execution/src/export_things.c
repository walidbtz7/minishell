/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:32:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/30 19:44:51 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <minishell.h>

char **export_sort(char **envp)
{
	int i;
	int x;
	char **export;
	char *tmp;
	
	i = 0;
	while(envp[i])
		i++;
	export = (char **)(malloc(i *sizeof(char *)));
	i = 0;
	while (envp[i])
	{
		export = ft_strdup(envp[i]);
		i++;
	}
	export[i] = 0;
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
			}
			free(tmp);
			x++;
		}
		i++;
	}
}

void	export_cmd(char **env,char **str)
{
	char **export;
	char **tmp;
	int i;
	i = 0;
	while (export[i])
		i++;
	export = export_sort(env);
	if(check_cmd_export(str))
	{
		if(str[0])
		{
			tmp = (char **)malloc(i+1 * sizeof(char *));
			i = 0;
			while (export[i])
			{
				tmp[i] = ft_strdup(export[i]);
				i++;
			}
			tmp[i] = ft_strdup(str[0]);
			tmp[i] = 0;
			
		}
			
	}
}