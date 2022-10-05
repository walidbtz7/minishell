/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:15:25 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/05 08:43:00 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strncmp( char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if(!s1 || !s2)
		return(0);
	if (n == 0)
		return (0);
	while ((i < n - 1) && (s1[i] != '\0')
		&& (s2[i] != '\0') && (s1[i] == s2[i]))
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
