/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imposter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:05:39 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 15:33:58 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

int	isimposter(int c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
