/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:15:25 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/30 17:50:13 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	if(!s2)
		return(0);
	i = 0;
	while ((s1[i] == s2[i]) && (s1[i]) && (s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
