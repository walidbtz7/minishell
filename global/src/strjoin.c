/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:23:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 16:49:08 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	p = (char *) malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (j < ft_strlen(s1))
	{
		p[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		p[j] = s2[i];
		i++;
		j++;
	}
	p[j] = '\0';
	return (p);
}
