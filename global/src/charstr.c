/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:05:39 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 15:31:07 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

char	*charstr(char c)
{
	char	*tmp;

	tmp = (char *) malloc(sizeof(char *) * 2);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}
