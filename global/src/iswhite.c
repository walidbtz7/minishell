/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iswhite.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:05:39 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/29 06:16:42 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

int iswhite(int c)
{
    if (c == 13 || c == 10 || c == ' ' || c == '\t')
        return (1);
    return (0);
}