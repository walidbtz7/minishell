/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:23:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/16 05:15:38 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char *ft_strjoin(char *s1, char *s2)
{
    int i;
    int j;
    char *p;
    int a;
    int b;

    j = 0;
    if (!s1 && !s2)
        return (0);
    if (!s1)
        s1 = ft_strldup("", 0);
    a = ft_strlen(s1);
    b = ft_strlen(s2);
    i = a + b;
    p = (char *)malloc(i + 1);
    if (!p)
        return (NULL);
    i = 0;
    while (j < a)
    {
        p[j] = s1[i];
        j++;
        i++;
    }
    i = 0;
    while (i < b)
    {
        p[j] = s2[i];
        i++;
        j++;
    }
    p[j] = '\0';
    return (p);
}
