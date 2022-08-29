/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strldup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:23:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/28 23:25:45 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char *ft_strldup(const char *s1, int len)
{
    char *p;
    int i;

    if (!s1)
        return (0);
    p = (char *)malloc(sizeof(char) * (len + 1));
    i = 0;
    if (!p)
        return (NULL);
    while (s1[i] && i < len)
    {
        p[i] = s1[i];
        i++;
    }
    p[i] = '\0';
    return (p);
}