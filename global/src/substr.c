/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:05:39 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 10:28:09 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int		a;

	if (!s)
		return (0);
	a = ft_strlen(s);
	if (start > a + 1)
		return (ft_strldup("", 0));
	if (a - start < len)
		len = a - start;
	p = (char *) malloc(len +1);
	if (!p)
		return (NULL);
	if (start <= a)
	{
		a = 0;
		while (s[start] != '\0' && a < len)
		{
			p[a++] = s[start++];
		}
		p[a] = '\0';
	}
	return (p);
}
