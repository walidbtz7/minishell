/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/16 09:58:44 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_cargv *init_cargv(char *src, char **envp)
{
    t_cargv *cargv;

    if(!src)
       return (NULL); 
    cargv = malloc(sizeof(t_cargv));
    cargv->src = src;
    cargv->i = 0;
    cargv->envp = envp;
    cargv->expand = 1;
    cargv->single = 0;
    cargv->dbl = 0;
    cargv->c = src[cargv->i];
    return (cargv);
}
char    *charstr(char c)
{
    char    *tmp;

    tmp = (char *) malloc(sizeof(char *) * 2);
    tmp[0] = c;
    tmp[1] = '\0';
    return (tmp);
}

void cargv_advence(t_cargv *cargv)
{
    if (cargv->c != '\0')
    {
        cargv->i++;
        cargv->c = cargv->src[cargv->i];
    }
    
}
int    envstop(char c)
{
    if(!isalnum(c) || c == '\0')
        return (0);
    return (1);
}

void single_quote(t_cargv *cargv)
{
    if(cargv->dbl == 0)
    {
        if(cargv->c == 39 && cargv->single == 0)
        {
            cargv->single = 1;
            cargv->expand = 0;
        }
        else if(cargv->c == 39 && cargv->single == 1)
        {
            cargv->single = 0;
            cargv->expand = 1;
        }
    }
}

void double_quote(t_cargv *cargv)
{
    if(cargv->single == 0)
    {
        if(cargv->c == 34 && cargv->dbl == 0)
            cargv->dbl = 1;
        else if(cargv->c == 34 && cargv->dbl == 1)
            cargv->dbl = 0;
    }
}

char   *getenval(char *key,char **envp)
{
    int i;
    int j;
    int exit;

    i = 0;
    exit = 0;
    if(!key)
        return (0);
    while (envp[i] && !exit)
    {
        j = 0;
        while (key[j] == envp[i][j] && key[j] && envp[i][j])
            j++;
        if(envp[i][j] == '=')
            exit = 1;
        else 
            i++;
    }
    if(envp[i])
        return (ft_substr(envp[i], j + 1 , ft_strlen(envp[i])));
    return (NULL);
}

char*    expandenv(t_cargv *cargv)
{
    char   *var;

    var = NULL;
    if(cargv->expand == 1)
    {   
        cargv_advence(cargv);
        if(!cargv->c)
            return "$";
        if(cargv->c == '?')
            return ("0");
        while (envstop(cargv->c))
        {
            var = ft_strjoin(var, charstr(cargv->c));
            cargv_advence(cargv);
        }
       var = getenval(var, cargv->envp);
       return (var);
    }
    return "$";
}

char *fargv(t_cargv *check)
{
    char    *new;

    new = NULL;
    while (check->c)
    {
        double_quote(check);
        single_quote(check);
        if(check->c == '$')
            new = ft_strjoin(new, expandenv(check));
        if (check->c != 34 && check->c != 39 && check->c != '$')
            new = ft_strjoin(new, charstr(check->c));
        else if(check->c == 34 && check->single == 1)
            new = ft_strjoin(new, charstr(check->c));
        else if(check->c == 39 && check->dbl == 1)
            new = ft_strjoin(new, charstr(check->c));
        cargv_advence(check);
    }
    return (new);
}
