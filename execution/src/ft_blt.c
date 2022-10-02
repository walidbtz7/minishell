/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:28:58 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/01 23:12:06 by mrafik           ###   ########.fr       */
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

int cd_fuction(char *path_cd,char **env)
{
	///char	*pwd;
	int		i;
	int		j;
	char	*save;
	//char	**search;
	
	write(2,"hna\n",4);
	if(chdir(path_cd))
		return(printf("faild to %s\n",path_cd));
	i = position(env,"PWD");
	j = position(env,"OLDPWD");
	save = ft_strdup(env[j]);
	env[j] = ft_strdup(env[i]);
	if (getcwd(NULL, 0))
		env[i] =  getcwd(NULL, 0);
	else
		env[i] = ft_strdup(save); 
	return(0);
	exit(0);
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

// void	builtins(char **str,char **env)
// {
// 	char **export;
	
// 	export = export_sort(env);
// 	if(!ft_strcmp(str[0],"cd"))
// 		{
// 			cd_fuction(str[1],env);
// 			free(export);
// 			export = export_sort(env);
// 		}
// 	if(!ft_strcmp(str[0],"echo"))
// 		echo_function(str);
// 	if(!ft_strcmp(str[0],"export"))
// 		export_cmd(env,str);
// }