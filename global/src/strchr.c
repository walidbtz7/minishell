/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:05:39 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 10:31:34 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char	*ft_strchr(char *s, int c)
{
	char	*str;

	str = (char *) s;
	if (!s)
		return (0);
	while (*str != '\0')
	{
		if (*str == (char) c)
			return (str);
		str++;
	}
	return (NULL);
}
