/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 12:33:45 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
void single_quote(char  c,int *single, int dbl)
{
    if(dbl == 0)
    {
        if(c == 39 && *single == 0)
            *single = 1;
        else if(c == 39 && *single == 1)
            *single = 0;
    }
}

void double_quote(char  c,int *dbl , int single)
{
    if(single == 0)
    {
        if(c == 34 && *dbl == 0)
            *dbl = 1;
        else if(c == 34 && *dbl == 1)
            *dbl = 0;
    }
}

char *rmquote(char   *str)
{
    int i;
    char   *new;
    char    tmp[2];
    int single;
    int dbl;

    i = 0;
    single = 0;
    dbl = 0;
    new = NULL;
    while (str[i])
    {
        single_quote(str[i],&single,dbl);
        double_quote(str[i],&dbl, single);
        tmp[0] = str[i];
        tmp[1] = '\0';
        if (str[i] != 34 && str[i] != 39)
            new = ft_strjoin(new, tmp);
        else if(str[i] == 34 && single == 1)
            new = ft_strjoin(new, tmp);
        else if(str[i] == 39 && dbl == 1)
            new = ft_strjoin(new, tmp);
       i++;
    }
    return (new);
}

char   *getenval(char *key,char **envp)
{
    int i;
    int j;
    int exit;

    i = 0;
    j = 0;
    exit = 0;
    if(!key)
        return (0);
    while (envp[i] != NULL && exit != 1)
    {
        j = 0;
        while (envp[i][j] && key[j] && key[j] == envp[i][j])
            j++;
        if(envp[i][j] != '=' && envp[i + 1] == NULL)
           i++;
        else
            exit = 1;
    }
    if(envp[i][j] == '=')
        return (ft_substr(envp[i], j + 1 , ft_strlen(envp[i])));
    return (NULL);
}

char *fargv(char   *str, char **envp)
{
    printf("%s\n",getenval("",envp));
    return rmquote(str);
}