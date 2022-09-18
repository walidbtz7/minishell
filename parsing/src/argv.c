/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/18 15:46:30 by wboutzou         ###   ########.fr       */
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
        while (key[j] == envp[i][j] && key && envp[i][j])
            j++;
        if(j == ft_strlen(key))
            exit = 1;
        else
            i++;
    }
    if(j == ft_strlen(key) &&  envp[i][j] == '=')
        return (ft_substr(envp[i], j + 1 , ft_strlen(envp[i])));
    return (NULL);
}

int    envstop(char c)
{
    if(isalnum(c) || c == '_')
        return (1);
    return (0);
}

char*    checkfirst(t_cargv *cargv)
{
    cargv_advence(cargv);
    if(!isnumber((int) cargv->c))
    {
        if(cargv->c == '?')
            return ("0");
        else if (!envstop(cargv->c))
            return ("$");
    }
    return (NULL);
}
char*   splitenv(char *str)
{
    char    **splited;
    char    *new;
    int     i;

    i = 0;
    new = NULL;
    splited = NULL;
    if(!str)
        return (NULL);
    splited = ft_split(str);
    while (splited[i])
    {
       if(i == 0)
            new = ft_strjoin(new, splited[i]);
       else
            new = ft_strjoin_sep(new, splited[i]);
       i++;
    }
    return (new);
}
char*    expandenv(t_cargv *cargv)
{
    char   *var;

    var = NULL;
    if(cargv->expand == 1)
    {
        var = checkfirst(cargv);
        if(var)
            return (var);
        while (envstop(cargv->c))
        {
            var = ft_strjoin(var, charstr(cargv->c));
            cargv_advence(cargv);
        }
       var = getenval(var, cargv->envp);
       return (var);
    }
    else
        cargv_advence(cargv);

    return "$";
}

char **fargv(t_cargv *check)
{
    char    *new;
    char    *expend;
    char    **test;

    new = ft_strldup("", 0);
    expend = NULL;
    test = NULL;
    while (check->c)
    {
        double_quote(check);
        single_quote(check);
        if(check->c == '$')
        {
            expend = expandenv(check);
            if(expend)
                new = ft_strjoin(new, expend);
            else 
                new = NULL;
        }
        else 
        {
            new = ft_strjoin(new, charstr(check->c));
           cargv_advence(check);
        }
    
    }
    if(new)
    {
        test = ft_split(new);
    }
    return (test);
}
char *rmquote(t_cargv *check)
{
    char    *new;
    char    *expend;

    new = ft_strldup("", 0);
    expend = NULL;
    while (check->c)
    {
        double_quote(check);
        single_quote(check);
        if (check->c != 34 && check->c != 39)
            new = ft_strjoin(new, charstr(check->c));
        else if(check->c == 34 && check->single == 1 )
            new = ft_strjoin(new, charstr(check->c));
        else if(check->c == 39 && check->dbl == 1 )
            new = ft_strjoin(new, charstr(check->c));
        cargv_advence(check);
    }
    return (new);
}