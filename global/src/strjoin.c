/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:23:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/22 21:03:46 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		s1 = ft_strldup("", 0);
	if (!s2)
		s2 = ft_strldup("", 0);
	i = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
		p[j++] = s1[i++];
	i = 0;
	while (s2[i])
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}
