# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <minishell.h>
// int ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 		i++;
// 	return(i);
// }
// static int	ft_size(char *str, char c)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (str[x] == c)
// 		x++;
// 	while (str[x] != '\0')
// 	{
// 		if (str[x] == c)
// 		{
// 			y++;
// 			while (str[x] == c)
// 				x++;
// 		}
// 		else
// 			x++;
// 	}
// 	return (++y);
// }

// void	ft_free_e(char **str)
// {
// 	int	i;

// 	i = 0;
// 	if (str)
// 	{
// 		while (str[i])
// 		{
// 			free(str[i++]);
// 		}
// 		free(str);
// 	}
// }
// static char	*ft_cm(char *str, const char *s, char c)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (s[x] != '\0')
// 	{
// 		if (s[x] == c)
// 			break ;
// 		x++;
// 	}
// 	str = (char *) malloc ((x + 1) * sizeof(char *));
// 	while (y < x)
// 	{
// 		str[y] = s[y];
// 		y++;
// 	}
// 	str[x] = '\0';
// 	return (str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**str;
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	if (!s)
// 		return (0);
// 	str = (char **) malloc ((ft_size((char *)s, c) + 1) * sizeof(char *));
// 	if (!str)
// 		return (0);
// 	while (s[y] != '\0')
// 	{
// 		if (s[y] != c)
// 		{
// 			str[x] = ft_cm(str[x], &s[y], c);
// 			x++;
// 			while (s[y] != c && s[y] != '\0')
// 				y++;
// 		}
// 		else
// 			y++;
// 	}
// 	str[x] = 0;
// 	return (str);
// }
// int	ft_strlen2(char **str)
// {
// 	int	i;

// 	i = 0;
// 	if (str)
// 	{
// 		while (str[i])
// 		i++;
// 	}
// 	return (i);
// }

// char	**ft_dup(char **str)
// {
// 	char	**tmp;
// 	int		i;

// 	i = ft_strlen2(str);
// 	tmp = (char **)malloc((i + 1) * sizeof(char *));
// 	i = 0;
// 	while (str[i])
// 	{
// 		tmp[i] = strdup(str[i]);
// 		i++;
// 	}
// 	tmp[i] = NULL;
// 	return (tmp);
// }


int exist(char **env,char *args)
{
	char **str;
	char **tmp;
	int i;

	i = 0;
	str = ft_split(args,'=');
	while (env[i])
	{
		tmp = ft_split(env[i],'=');
		if(!strcmp(str[0],tmp[0]))
			return(i);
		free(tmp);
		i++;
	}
	return(-1);
}
void ft_stock(char ***env,char *args)
{	
	int i;
	char **tmp;

	i = exist((*env),args);
	if(ft_strchr(args,'='))
	{
		if(i > 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(args);
		}
		else
		{
			printf("new and =\n");
			tmp = *env;
			(*env) = (char **)(malloc((ft_strlen2(*env)+2) * sizeof(char *)));
			i = 0;
			while((tmp)[i])
			{
				(*env)[i] = tmp[i];
				i++;
			}
			(*env)[i] = ft_strdup(args);
			(*env)[i+1] = 0;
		}
	}
	else
	{
		tmp = *env;
		(*env) = (char **)(malloc((ft_strlen2(*env)+2) * sizeof(char *)));
		i = 0;
		while((tmp)[i])
		{
			(*env)[i] = tmp[i];
			i++;
		}
		(*env)[i] = ft_strdup(args);
		(*env)[i+1] = 0;
	}
}

void ft_export(char ***env,char ***export,char **args)
{
	int i;
	i = 1;

	while(args[i])
	{
		if(check_cmd_export(args[i]))
		{
			if(ft_strchr(args[i],'='))
				ft_stock(env,args[i]);
			ft_stock(export,args[i]);
		}
		i++;
	}
	// i = 0;
	// while ((*env)[i])
	// 	printf("%s\n",(*env)[i++]);
	
}

// int main(int ac,char **args,char **envp)
// {
	
// 	char **env;
// 	char **export;
// 	int i;

// 	env = ft_dup(envp);
// 	export = ft_dup(envp);
// 	while (1)
// 	{
// 		printf("uouo\n");
// 		if(strcmp(args[1],"export"))
// 		{
// 			i = 0;
// 			while(export[i])
// 			{
// 				printf("%s\n",export[i++]);
// 			}
// 		}
// 		else if(strcmp(args[1],"env"))
// 		{
// 			i = 0;
// 			while(env[i])
// 			{
// 				printf("%s\n",env[i++]);
// 			}
// 		}
// 		else
// 			ft_export(&env,&export,args);
// 	}
// }

	
